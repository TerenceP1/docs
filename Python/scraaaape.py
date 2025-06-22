from playwright.sync_api import sync_playwright
import random
import time

js_init_script = """
(function() {
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

with sync_playwright() as p:
    browser = p.chromium.launch(headless=False)
    context = browser.new_context()
    pages = []
    context.add_init_script(js_init_script)
    def handle_new_page(new_page):
        print("🆕 New tab opened.")
        pages.append(new_page)
        try:
            new_page.wait_for_load_state('load', timeout=10000)
        except:
            print("⚠️ New tab failed to load")

    context.on("page", handle_new_page)

    # Start with one main page
    main_page = context.new_page()
    pages.append(main_page)
    main_page.goto("https://example.com")
    main_page.wait_for_load_state('networkidle')
    

    for i in range(2000):
        open_pages = [p for p in pages if not p.is_closed()]
        if not open_pages:
            print("❌ No open pages left.")
            break

        current_page = random.choice(open_pages)
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

        try:
            current_page.mouse.move(x, y)
            current_page.mouse.click(x, y)
            print(f"🖱️ Clicked at ({x}, {y}) on {current_page.url}")
        except Exception as e:
            print(f"⚠️ Error clicking at ({x}, {y}): {e}")

        time.sleep(random.uniform(0.01, 0.1))

    time.sleep(60)
    browser.close()
