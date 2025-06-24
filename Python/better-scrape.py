from urllib.robotparser import RobotFileParser
import asyncio
import random
from playwright.async_api import async_playwright
from playwright.async_api import TimeoutError

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

async def click_with_navigation_check(page, i):
    try:
        async with page.expect_navigation(timeout=5000):
            tag = await i.evaluate("(el) => el.tagName.toLowerCase()")
            await page.bring_to_front()
            if tag == "a":
                await i.click(button="middle")
                print("LINK")
            else:
                await i.click()
        print("Navigation detected!")
        print("Navigation detected!")
        print("Navigation detected!")
        print("Navigation detected!")
        print("Navigation detected!")
        await page.wait_for_load_state("load")
        url = page.url
        new_page = await context.new_page()
        await new_page.goto(url)
        # Undo navigation
        await page.go_back()
        print("Returned to previous page.")
    except TimeoutError:
        print("No navigation happened, continuing as normal.")


domain_seed="https://google.com"

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
    # Click
    elements = await page.query_selector_all("*:visible")
    await asyncio.sleep(1)
    for i in elements:
        asyncio.create_task(click_with_navigation_check(page,i))
        #await asyncio.sleep(1)
        #print("CLICK")

def nPage(page):
    asyncio.create_task(new_page_handeler(page))

async def main():
    global context
    async with async_playwright() as p:
        # Launch Chromium browser (headless=False to see the browser)
        browser = await p.chromium.launch(headless=False)
        context = await browser.new_context(
            permissions=[],          # grant no permissions at all
        geolocation=None,        # disable geolocation
        locale="en-US"           # optional: set locale
        )
        context.on("page",nPage)
        # Open a new page/tab
        page = await context.new_page()
        
        # Navigate to example.com
        await page.goto("https://google.com")
        nPage(page)
        asyncio.create_task(sift_duplicate_pages_loop())
        
        await asyncio.sleep(600)
        # Close the browser
        await browser.close()

# Run the async main function
asyncio.run(main())