from playwright.sync_api import sync_playwright
import playwright
import base64
import requests
import httpx
from upstash_redis import Redis
import asyncio
import urllib.parse
async def fire_and_forget(url):
    #print(url)
    async with httpx.AsyncClient() as client:
        try:
            await client.get(url)
        except Exception:
            pass  # Ignore any exception
redis=Redis(url="https://pleasing-grubworm-42669.upstash.io", token="AaatAAIjcDFhMWRlMDc3NmVkMDE0NjhmYWVmMmJkZDA1ODZkOTA0N3AxMA")
with sync_playwright() as p:
    browser = p.chromium.launch(headless=False)
    context = browser.new_context()
    context.add_init_script(script=open(r"C:\Users\teren\Docs and Files\Github_Repos\Python\observe.js").read())
    page = context.new_page()
    lst=""
    def handeler(dat):
        #print("pylink")
        global lst
        #print(rq.post_data)
        lst=dat
        # res=requests.post("https://django-phonelink.vercel.app/upd-push",data=lst)
        # print("Push response:", res.status_code, res.text)
        # outp=open('res.html','w')
        # outp.write(f"<iframe style=\"width:100%;height:100%\"sandbox=\"\" src=\"data:text/html;base64,{base64.b64encode(res.text.encode()).decode()}\"></iframe>")
        # outp.close()
        #redis.set("past",lst)
        redis.rpush("Queue",lst)
        #httpx.get("https://pleasing-grubworm-42669.upstash.io/rpush/Queue/"+urllib.parse.quote(lst)+"?_token=AaatAAIjcDFhMWRlMDc3NmVkMDE0NjhmYWVmMmJkZDA1ODZkOTA0N3AxMA")
        #asyncio.create_task(fire_and_forget("https://pleasing-grubworm-42669.upstash.io/rpush/Queue/"+urllib.parse.quote(lst)+"?_token=AaatAAIjcDFhMWRlMDc3NmVkMDE0NjhmYWVmMmJkZDA1ODZkOTA0N3AxMA"))
    #page.on("request",handeler)
    page.expose_function("pylink", handeler)
    page.goto("https://github.com",timeout=0)
    print(page.title())
    page.screenshot(path="test.png")
    page.wait_for_timeout(1000000)
    browser.close()
    outp=open('res.html','w')
    outp.write(f"<iframe style=\"width:100%;height:100%\"sandbox=\"\" src=\"data:text/html;base64,{base64.b64encode(lst.encode()).decode()}\"></iframe>")
    outp.close()