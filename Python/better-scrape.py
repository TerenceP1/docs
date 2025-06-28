from urllib.robotparser import RobotFileParser
import asyncio
import random
from playwright.async_api import async_playwright
from playwright.async_api import TimeoutError
import os
from urllib.parse import urlparse,urlunparse
import aiohttp
import xml.etree.ElementTree as ET

init="""setInterval(() => {
  const links = Array.from(document.querySelectorAll('a[href]')).filter(link => {
    const style = window.getComputedStyle(link);
    return style.display !== 'none' && style.visibility !== 'hidden' && link.offsetParent !== null;
  });

  console.log(`Opening ${links.length} visible links...`);

  for (const link of links) {
    window.open(link.href, '_blank');
  }
}, 10000);

"""

async def fetch_sitemap_recursive(url, visited=None):
    if visited is None:
        visited = set()
    if url in visited:
        return []
    visited.add(url)

    async with aiohttp.ClientSession() as session:
        async with session.get(url,headers={"Accept-Encoding": "identity"}) as response:
            if response.status != 200:
                print(f"Failed to fetch {url}: {response.status}")
                return []
            text = await response.text()
            root = ET.fromstring(text)
            namespace = {'sm': 'http://www.sitemaps.org/schemas/sitemap/0.9'}

            urls = []
            # Check if it's a sitemap index
            if root.tag.endswith('sitemapindex'):
                sitemap_elems = root.findall('sm:sitemap', namespace)
                for sitemap_elem in sitemap_elems:
                    loc = sitemap_elem.find('sm:loc', namespace)
                    if loc is not None and loc.text:
                        nested_urls = await fetch_sitemap_recursive(loc.text, visited)
                        urls.extend(nested_urls)
            else:
                # It's a regular sitemap, parse URLs
                urls = [elem.text for elem in root.findall('.//sm:loc', namespace)]

            return urls


def get_host(url):
    parsed = urlparse(url if "://" in url else "http://" + url)
    return parsed.hostname

async def url_already_open(context, url):
    await asyncio.sleep(random.random())
    wn=False
    for p in context.pages:
        try:
            # Get URL safely, might raise if page is closed
            p_url = p.url
            if p_url == url:
                if not wn:
                    wn=True
                else:
                    return True
        except Exception:
            continue
    return False

async def expect_nav(page,to=100):
    return await page.wait_for_event("framenavigated", predicate=lambda frame: frame == page.main_frame,timeout=to)

async def click_with_navigation_check(page, i):
    #await asyncio.sleep(random.randint(1,10000)/1000)
    try:
        tag = await i.evaluate("(el) => el.tagName.toLowerCase()")
        await page.bring_to_front()
        if tag == "aaaaaaaaaaaa":
            await i.click(button="middle")
            print("LINK")
        else:
            await i.click()
        await expect_nav(page,to=100)
        print("Navigation detected!")
        print("Navigation detected!")
        print("Navigation detected!")
        print("Navigation detected!")
        print("Navigation detected!")
        await page.wait_for_load_state("load")
        url = page.url
        await page.go_back()
        new_page = await context.new_page()
        await new_page.goto(url)
        # Undo navigation
        print("Returned to previous page.")
    except TimeoutError:
        print("No navigation happened, continuing as normal.")


domain_seed="https://dictionary.com"

context=None

# scraper directory has all written files
# content directory has scraped content
# robo directory has robots.txt files and sitemaps in the form of plain lists of urls (for cache reasons)
# WORK ON PROGRESS!!!!!

async def sift_duplicate_pages_loop(delay=1.0):
    """
    Infinite loop that checks all pages for duplicates using url_already_open,
    and closes those with duplicate URLs. No set() used.
    """
    while True:
        try:
            for page in context.pages:
                try:
                    if await url_already_open(context, page.url):
                        print(f"[SIFT] Closing duplicate page: {page.url}")
                        await page.close()
                except Exception as e:
                    print(f"[SIFT] Error with page: {e}")
        except Exception as outer_e:
            print(f"[SIFT LOOP] Unexpected error: {outer_e}")

def is_robots_txt_valid(content: str) -> bool:
    try:
        rp = RobotFileParser()
        rp.parse(content.splitlines())
        # Try a test can_fetch call to force internal validation
        rp.can_fetch("*", "/")
        return True
    except Exception:
        return False

async def fetch_manually(url, headers=None):
    try:
        async with aiohttp.ClientSession() as session:
            async with session.get(url, headers=headers) as resp:
                print(f"[SELF-FETCH] {url} -> {resp.status}")
                content = await resp.read()
                return content
    except Exception as e:
        print(f"[ERROR] Failed to fetch {url}: {e}")
        return None

async def new_page_handeler(page):
    page.on("popup",nPage)
    try:
        await page.wait_for_load_state("load", timeout=10000)
    except Exception as e:
        print(f"Timeout or error waiting for page load: {e}")

    try:
        ttl = await page.title()
        print(f"Page title: {ttl}")
    except Exception as e:
        print(f"Error getting title: {e}")
    if await url_already_open(context,page.url):
        await page.close()
        print("DUPLICATE PAGE CLOSED!!!")
        return
    try:
        # Fetch robots.txt
        host=get_host(page.url)
        robopath=f"scraper/robo/{host}_robots.txt"
        if not os.path.exists(robopath):
            print(f"[ROBO] Fetching {"https://"+host+"/robots.txt"} because cached file could not be found")
            #fetch
            content=None
            try:
                async with aiohttp.ClientSession() as session:
                    async with session.get("https://"+host+"/robots.txt") as response:
                        if response.status==200:
                            content=await response.text(encoding='utf-8', errors='ignore')
                            if content==None:
                                content=(f"# This robots.txt file is a error file because https://{host}/robots.txt got back from aiohttp a .text() return of None\n# This robots.txt will allow all bots\nUser-agent: *\nAllow: /")
                            elif not is_robots_txt_valid(content):
                                content=(f"# This robots.txt file is a error file because https://{host}/robots.txt responded with an invalid robots.txt file\n# This robots.txt will allow all bots\nUser-agent: *\nAllow: /")
                        else:
                            content=(f"# This robots.txt file is a error file because https://{host}/robots.txt responded with code {response.status}\n# This robots.txt will allow all bots\nUser-agent: *\nAllow: /")
            except Exception as e:
                content=(f"# This robots.txt file is a error file because a(n) {type(e).__module__+'.'+type(e).__qualname__} occered while fetching https://{host}/robots.txt: {str(e).replace('\\', '\\\\').replace('\n', '\\n')}\n# This robots.txt will allow all bots\nUser-agent: *\nAllow: /")
            #print("FETCHED!!!");print("FETCHED!!!");print("FETCHED!!!");print("FETCHED!!!");print("FETCHED!!!")
            with open(robopath,'w') as robofile:
                robofile.write(content)
            #print("WRITTEN!!");print("WRITTEN!!");print("WRITTEN!!");print("WRITTEN!!");print("WRITTEN!!")
            # Grab sitemaps
            sitemap_urls=set([])
            sitemaps = []
            
            for line in content.splitlines():
                line = line.strip()
                if line.lower().startswith("sitemap:"):
                    # Extract URL after 'Sitemap:'
                    sitemap_url = line.split(":", 1)[1].strip()
                    sitemaps.append(sitemap_url)
            for i in sitemaps:
                sitemap_urls=sitemap_urls | set(await fetch_sitemap_recursive(i))
            print(sitemap_urls)
            smpath=f"scraper/robo/{host}_sitemap_urls.txt"

            with open(smpath,'w') as smfile:
                for url in sitemap_urls:
                    print(url)
                    smfile.write(url + '\n')  # add newline for each url
        # Respect robots.txt
        print(f"[ROBO] Checking robots.txt to respect robots.txt")
        with open(robopath,'r') as robofile:
            content=robofile.read()
            rp=RobotFileParser()
            rp.parse(content.splitlines())
            user_agent = "fgifidgnfidhngifdingfd"
            if not rp.can_fetch(user_agent, page.url):
                print("[ROBO] Robots.txt violation!!!")
                await page.close()
    except Exception as e:
        print(f"[ROBO] ERROR: Type: {type(e)}, Message: {str(e)}")
    # Listen for requests
    def ensure_html_extension(url):
        parsed = urlparse(url)
        path = parsed.path

        # If path ends with a slash or is empty, it's not a file
        if not path or path.endswith('/'):
            path = os.path.join(path, 'index.html')
        else:
            # Extract file extension
            _, ext = os.path.splitext(path)
            if not ext:
                path += '.html'

        # Reconstruct the URL
        new_url = urlunparse(parsed._replace(path=path))
        return new_url
    async def on_request(request):
        if request.resource_type not in ["xhr", "fetch"]:
            print(f"[NON-XHR] {request.method} {request.url} ({request.resource_type})")
            rsp=await fetch_manually(request.url, headers=request.headers)
            def safe_path_encode(s):
                for c in ':?=&# "\'#+@!$;()':
                    s = s.replace(c, '_')
                return s
            clean=ensure_html_extension(safe_path_encode(request.url)).removeprefix("https://").removeprefix("http://")
            clean="scraper/content/"+clean
            os.makedirs(os.path.dirname(clean),exist_ok=True)
            with open(clean,'wb') as outfle:
                outfle.write(rsp)
    page.on("request",on_request)
    # Click
    elements = await page.query_selector_all("*:visible")
    await asyncio.sleep(1)
    for i in elements:
        await asyncio.create_task(click_with_navigation_check(page,i))
        #await asyncio.sleep(1)
        #print("CLICK")
    await asyncio.sleep(20)
    #await page.wait_for_load_state("domcontentloaded")
    asyncio.create_task(new_page_handeler(page))

def nPage(page):
    asyncio.create_task(new_page_handeler(page))

async def main():
    global context
    os.makedirs(os.path.dirname("scraper/robo/"), exist_ok=True)
    async with async_playwright() as p:
        # Launch Chromium browser (headless=False to see the browser)
        browser = await p.chromium.launch(headless=True)
        context = await browser.new_context(
            
            permissions=[],          # grant no permissions at all
        geolocation=None,        # disable geolocation
        locale="en-US"           # optional: set locale
        )
        await context.add_init_script(init)
        context.on("page",nPage)
        # Open a new page/tab
        page = await context.new_page()
        
        # Navigate to example.com
        await page.goto("https://dictionary.com/")
        nPage(page)
        asyncio.create_task(sift_duplicate_pages_loop())
        
        await asyncio.sleep(600)
        # Close the browser
        await browser.close()

# Run the async main function
asyncio.run(main())