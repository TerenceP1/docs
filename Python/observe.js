/* window.addEventListener("load", */(function(){
    function makeUrlsAbsolute(doc) {
        const attrs = ["href", "src", "action"];
        const all = doc.querySelectorAll("*");
        for (const el of all) {
            for (const attr of attrs) {
                if (el.hasAttribute(attr)) {
                    const val = el.getAttribute(attr);
                    if (val && !val.startsWith("http") && !val.startsWith("data:") && !val.startsWith("javascript:")) {
                        try {
                            const abs = new URL(val, document.baseURI).href;
                            el.setAttribute(attr, abs);
                        } catch (e) { }
                    }
                }
            }
        }
    }
    function pathify(node){
        let base=document/* .documentElement */;
        let cn=node;
        let iRes=[];
        while (cn!==base){
            let pNode=cn.parentNode;
            if (pNode===null){
                break;
            }
            let nodeID=Array.from(pNode.childNodes).indexOf(cn);
            iRes.push(nodeID);
            cn=pNode;
        }
        return iRes.reverse();
    }
    function obCB(records,ob){
        let url="https://github.com"
        for (let record of records)
        {
            docCpy=document.cloneNode(true);
            makeUrlsAbsolute(docCpy);
            if (record.type==="characterData"){
                pylink(
                JSON.stringify({"type":"cData","node":pathify(record.target),"value":record.target.data}));
            }
            else if (record.type==="attributes"){
                pylink(JSON.stringify({"type":"attr","node":pathify(record.target),"attr":record.attributeName,"nTName":record.target.getAttribute(record.attributeName)}));
            }
            else if (record.type==="childList"){
                let added=[];
                let removed=record.removedNodes.length;
                for (let node of record.addedNodes){
                    if (node.nodeType === Node.ELEMENT_NODE) {
                        added.push(node.outerHTML);
                    } else if (node.nodeType === Node.TEXT_NODE || node.nodeType === Node.CDATA_SECTION_NODE) {
                        added.push(node.data);
                    } else {
                        added.push(node.textContent || "");
                    }
                }
                
                pylink(JSON.stringify({"type":"child","node":pathify(record.target),"added":added,"removed":removed,"nSib":record.nextSibling===null?-1:(Array.from(record.target.childNodes).indexOf(record.nextSibling)- added.length)}));
            }
        }
        // fetch("https://unblocked2.vercel.app/example.com/876854365838653",{
        //     body:docCpy.documentElement.outerHTML,
        //     method:"POST"
        // });
    }
    let obs=new MutationObserver(obCB);
    obs.observe(document,{ 
        subtree:true,
        childList:true,
        attributes:true,
        characterData:true
    });
}/* ); */)()