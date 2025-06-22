from playwright.sync_api import sync_playwright
import random
import time
import requests
import os
import re
import numpy as np
import cv2

from urllib.parse import urlparse, urlunparse

def get_with_browser_headers(url,hs):
    print("FETCHEING\nFETCHING")
    # os.system("start cmd")
    headers = {
        "User-Agent": ("Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
                       "AppleWebKit/537.36 (KHTML, like Gecko) "
                       "Chrome/114.0.0.0 Safari/537.36"),
        "Accept": ("text/html,application/xhtml+xml,application/xml;"
                   "q=0.9,image/webp,image/apng,*/*;q=0.8"),
        "Accept-Language": "en-US,en;q=0.9",
        "Accept-Encoding": "identity",
        "Connection": "keep-alive",
        "Upgrade-Insecure-Requests": "1",
        # Add more headers as needed
    }
    response = requests.get(url, headers=hs)
    print("FETCHED\nFETCHED")
    # os.system("start cmd")
    return response

def add_html_extension(url):
    parsed = urlparse(url)
    path = parsed.path

    if len(re.findall("/.*\..*",path))==0:
        # Append '.html' if the path doesn't end with it
        if path.endswith('/'):
            path = path[:-1]  # remove trailing slash first
        path += '.html'

        # Rebuild the URL with updated path
        parsed = parsed._replace(path=path)
        return urlunparse(parsed)
    return url

js_init_script = """
(function() {
document.addEventListener('load', () => {
  // Your code here runs after DOM is loaded
if (window.location.href === 'about:blank') {
  window.close();
}
setTimeout(() => window.close(), 30000);
});
    var seen = {};
    var queue = [];
    var timer = null;

    function normalizeUrl(url) {
        try {
            var u = new URL(url);
            u.hash = '';  // Ignore fragment
            // Optional: ignore query parameters by uncommenting the next line:
            // u.search = '';
            // Convert hostname and pathname to lowercase for uniformity
            u.hostname = u.hostname.toLowerCase();
            u.pathname = u.pathname.replace(/\/+$/, ''); // remove trailing slash
            return u.toString();
        } catch (e) {
            return url; // fallback: use raw URL if parsing fails
        }
    }

    function openNextLink() {
        if (queue.length === 0) return;
        var rawHref = queue.shift();
        var href = normalizeUrl(rawHref);

        if (!seen[href] && href.indexOf('http') === 0) {
            seen[href] = true;
            if (href=="about:blank"){return;}
            window.open(href, '_blank');
        }
    }

    function processQueue() {
        if (timer) return;
        timer = setInterval(function() {
            if (queue.length === 0) {
                clearInterval(timer);
                timer = null;
            } else {
                openNextLink();
            }
        }, 1500);
    }

    function queueLink(href) {
        var normalized = normalizeUrl(href);
        if (!seen[normalized] && normalized.indexOf('http') === 0) {
            queue.push(href);
            processQueue();
        }
    }

    function handleMutations(mutations) {
        var linksToAdd = [];
        mutations.forEach(function(mutation) {
            var nodes = mutation.addedNodes;
            for (var i = 0; i < nodes.length; i++) {
                var node = nodes[i];
                if (node.nodeType !== 1) continue;

                if (node.tagName === 'A' && node.href) {
                    linksToAdd.push(node.href);
                }

                var descendants = node.querySelectorAll && node.querySelectorAll('a[href]');
                if (descendants) {
                    for (var j = 0; j < descendants.length; j++) {
                        linksToAdd.push(descendants[j].href);
                    }
                }
            }
        });

        function addLinksSlowly(index) {
            if (index >= linksToAdd.length) return;
            queueLink(linksToAdd[index]);
            setTimeout(function() {
                addLinksSlowly(index + 1);
            }, 300);
        }
        addLinksSlowly(0);
    }

    function setup() {
        var existingLinks = Array.prototype.map.call(document.querySelectorAll('a[href]'), function(a) { return a.href; });
        function addExistingLinks(index) {
            if (index >= existingLinks.length) return;
            queueLink(existingLinks[index]);
            setTimeout(function() {
                addExistingLinks(index + 1);
            }, 300);
        }
        addExistingLinks(0);

        var observer = new MutationObserver(handleMutations);
        observer.observe(document.body, { childList: true, subtree: true });
    }

    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', setup);
    } else {
        setup();
    }
})();

"""

def close_duplicate_tabs(context):
    seen_urls = set()
    for page in context.pages:
        url = page.url
        if url=="about:blank":
            page.close()
        if url in seen_urls:
            print(f"Closing duplicate tab: {url}")
            page.close()
        else:
            seen_urls.add(url)

def dump_tabs_to_file(context, filename="open_tabs.txt"):
    with open(filename, "w", encoding="utf-8") as f:
        for page in context.pages:
            try:
                url = page.url
                title = page.title()
                f.write(f"{title} — {url}\n")
            except Exception as e:
                f.write(f"Error reading page info: {e}\n")
def remove_https(url):
    if url.startswith("https://"):
        return url[len("https://"):]
    return url
with sync_playwright() as p:
    browser = p.chromium.launch(headless=True)
    context = browser.new_context()
    pages = []
    context.add_init_script(js_init_script)
    #INIT
    def sanitize_url_for_filename(url):
        # Remove query and fragment
        parsed = urlparse(url)
        clean_path = parsed.path
        if clean_path.endswith("/"):
            clean_path = clean_path[:-1]
        if not re.search(r'\.\w+$', clean_path):
            clean_path += ".html"

        safe_path = os.path.join(parsed.netloc, clean_path.lstrip("/"))
        # Replace illegal filename characters
        safe_path = re.sub(r'[<>:"|?*]', '_', safe_path)
        return safe_path
    #REQUEST DOWNLOAD LOG
    def rqhandle(request):
        if not (request.resource_type in ["xhr","fetch"]):
            if request.method == "GET":
                rsp=requests.get(request.url,headers=request.headers)
                os.makedirs(os.path.dirname("scraped/"+sanitize_url_for_filename(remove_https(add_html_extension(request.url)))), exist_ok=True)
                scraped=open("scraped/"+sanitize_url_for_filename(remove_https(add_html_extension(request.url))),'wb')
                scraped.write(rsp.content)
                scraped.close()
    def limit_tab_count(context, max_tabs=20):
        pages = context.pages
        if len(pages) > max_tabs:
            to_close = random.sample([p for p in pages if not p.is_closed()], len(pages) - max_tabs)
            for p in to_close:
                try:
                    print(f"❌ Closing tab: {p.url}")
                    p.close()
                except Exception as e:
                    print(f"⚠️ Failed to close tab: {e}")
    #NEW PAGE HANDELER
    def handle_new_page(new_page):
        new_page.on("request",rqhandle)
        pages.append(new_page)
        print("⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️ PAGE PAGE PAGE PAGE PAGE ⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️\n⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️ PAGE PAGE PAGE PAGE PAGE ⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️\n⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️ PAGE PAGE PAGE PAGE PAGE ⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️\n⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️ PAGE PAGE PAGE PAGE PAGE ⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️\n⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️ PAGE PAGE PAGE PAGE PAGE ⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️\n")
        #os.system("start cmd")
        new_page.on("popup", handle_new_page)
        def on_main_request(request):
            if request.resource_type == "document" and request.is_navigation_request() and request.redirected_from:
                print(f"🔁 Redirected: {request.redirected_from.url} → {request.url}")
                handle_new_page(new_page)

        new_page.on("request", on_main_request)
        main_request = None

        def is_main_document_request(request):
            return request.resource_type == "document"
        headers=None
        try:
            main_request = new_page.wait_for_event("request", predicate=is_main_document_request, timeout=60000)
            headers=main_request.headers
        except Exception as e:
            print(f"ERROR:::::::::::: {e}")
            headers={
                "User-Agent": ("Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
                            "AppleWebKit/537.36 (KHTML, like Gecko) "
                            "Chrome/114.0.0.0 Safari/537.36"),
                "Accept": ("text/html,application/xhtml+xml,application/xml;"
                        "q=0.9,image/webp,image/apng,*/*;q=0.8"),
                "Accept-Language": "en-US,en;q=0.9",
                "Accept-Encoding": "identity",
                "Connection": "keep-alive",
                "Upgrade-Insecure-Requests": "1",
                # Add more headers as needed
            }


        print("🆕 New tab opened.")
        try:
            new_page.wait_for_load_state('load', timeout=10000)
            new_page.wait_for_url(re.compile(r'^https?://'), timeout=10000)
            os.makedirs(os.path.dirname("scraped/"+sanitize_url_for_filename(remove_https(add_html_extension(new_page.url)))), exist_ok=True)
            scraped=open("scraped/"+sanitize_url_for_filename(remove_https(add_html_extension(new_page.url))),'wb')
            scraped.write(get_with_browser_headers(new_page.url,headers).content)
            scraped.close()
        except Exception as e:
            print(f"⚠️ New tab failed to load. Error message: {e}")
            limit_tab_count(context,30)
    context.on("page", handle_new_page)




    # Start with one main page
    main_page = context.new_page()
    #handle_new_page(main_page)
    pages.append(main_page)
    main_page.goto("https://google.com", wait_until='commit',timeout=0)
    #main_page.wait_for_load_state('networkidle')
    """  # Start with one main page
    p2 = context.new_page()
    #handle_new_page(main_page)
    pages.append(p2)
    p2.goto("https://google.com")
    p2.wait_for_load_state('networkidle') """

    """ # Start with one main page
    p3 = context.new_page()
    #handle_new_page(main_page)
    pages.append(p3)
    p3.goto("https://bing.com")
    p3.wait_for_load_state('networkidle') """
    print("LOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\nLOOP!!!!!!!!!!!!!LOOOOOOOOOOOOOOOOOOP!!!!!!!!!!!\n")
    #PAGE MADE
    for i in range(2000):
        #CLIIIICK
        open_pages = [p for p in pages if not p.is_closed()]
        if not open_pages:
            print("❌ No open pages left.")
            break

        current_page = random.choice(open_pages)
        print("SWITCH\nSWITCH\nSWITCH\nSWITCH\nSWITCH\nSWITCH\nSWITCH\n")
        try:
            current_page.wait_for_load_state('domcontentloaded', timeout=3000)
            current_page.bring_to_front()
        except:
            pass

        viewport = current_page.viewport_size or {"width": 1280, "height": 720}
        width = viewport['width']
        height = viewport['height']
        x = random.randint(0, width - 1)
        y = random.randint(0, height - 1)
        print("CLICK\nCLICK\nCLICK\nCLICK\nCLICK\nCLICK\nCLICK\nCLICK\n")
        try:
            current_page.mouse.move(x, y)
            current_page.mouse.click(x, y)
            print(f"🖱️ Clicked at ({x}, {y}) on {current_page.url}")

            close_duplicate_tabs(context)
            dump_tabs_to_file(context)
        except Exception as e:
            print(f"⚠️ Error clicking at ({x}, {y}): {e}")
        screenshot_bytes = current_page.screenshot()
        time.sleep(random.uniform(0.01, 0.1))
        # Convert bytes to numpy array
        nparr = np.frombuffer(screenshot_bytes, np.uint8)

        # Decode image from memory (PNG/JPEG)
        img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)

        # Display with OpenCV
        cv2.imshow('Screenshot', img)
        cv2.waitKey(0)  # Wait for a key press to close window
        cv2.destroyAllWindows()

    time.sleep(60)
    browser.close()
