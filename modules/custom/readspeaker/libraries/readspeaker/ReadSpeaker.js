window.ReadSpeakerDefer={deferred:null,clickhandler:function(b){var b=b||window.event,e=b.target||b.srcElement;3===e.nodeType&&(e=e.parentNode);if(e!==document&&window.ReadSpeakerDefer.isRSLink(e)){window.ReadSpeakerDefer.deferred=e;if((e=window.ReadSpeakerDefer.findRSParent(e))&&e.className&&!/rsdeferred/i.test(e.className))e.className+=" rsdeferred";b.cancelBubble=!0;b.preventDefault&&b.preventDefault();b.stopPropagation&&b.stopPropagation();return!1}},init:function(){this.RSDeferClick(document)},
isRSLink:function(b){return this.isRSParent(b.parentNode)||b.href&&-1<b.href.indexOf("readspeaker.com/cgi-bin/rsent")},isRSParent:function(b){return b?b.className&&-1<b.className.indexOf("rsbtn")||b.id&&"string"===typeof b.id&&-1<b.id.indexOf("readspeaker_button"):!1},findRSParent:function(b){for(;b.parentNode&&b.parentNode!==document&&!(b=b.parentNode,"a"==b.tagName.toLowerCase()&&this.isRSLink(b)););return b==document?void 0:b.parentNode},RSDeferClick:function(b){b.addEventListener?b.addEventListener("click",
this.clickhandler,!1):b.attachEvent?b.attachEvent("onclick",this.clickhandler):b.onclick=this.clickhandler}};window.ReadSpeakerDefer.init();
(function(b){var e,f={major:"2",minor:"5",update:"4",revision:"1728",prod:"embhl"},h=[],G=0,t=0,H=!1,u=[],I=0,l=[],J=!1,q=[],B=!1,K=0,v=!1,w=null,j="default",L=!1,x=[],M=!1,T={},N="",C={},O=!1,D=function(a){if("string"==typeof a){for(var a="ReadSpeaker."+a.replace("_","."),a=a.split("."),d=b,c=0,y=a.length;c<y;c++)if(d)if(d[a[c]]){if(c==y-1)return d[a[c]];d=d[a[c]]}else break;else break;return!1}},P=function(a,d){u.push(a);I++;d||(d=[a]);for(var c=0,y=d.length;c<y;c++)try{var g=D(d[c]);"function"==
typeof g.init&&g.init.apply(g,[])}catch(e){r("[rspkr] Could not load: "+d[c]+" | "+e,3)}I==t&&!0===H&&(r("[rspkr] All prod mods loaded. _domready = "+v,4),c=function(){var a=b.ReadSpeaker;a.Common&&(a.c=a.Common);a.c&&(a.evt=a.c.addEvent,a.devt=a.c.dispatchEvent);a.c&&a.c.Settings&&(a.c.s=a.c.Settings);a.c.s&&(a.st=a.c.s);a.lib&&(a.l=a.lib);a.l&&a.lib.Facade&&(a.l.f=a.lib.Facade);a.l&&(a.l.f&&a.l.f.adapter)&&(a.l.f.a=a.l.f.adapter);a.modmap&&(a.m=a.modmap);a.pub&&a.pub.Config&&(a.pub.c=a.pub.Config);
a.pub.c&&(a.cfg=a.pub.c);a.PlayerAPI&&(a.pl=a.PlayerAPI);a.HL&&(a.hl=a.HL);a.ui&&(a.u=a.ui);b.ReadSpeaker.Common.dispatchEvent("onModsLoaded",b);b.ReadSpeaker.Common.dispatchEvent("onAfterModsLoaded",b);C.onAdapterReady?b.ReadSpeaker.Common.dispatchEvent("onReady",b):b.ReadSpeaker.Common.addEvent("onAdapterReady",function(){b.ReadSpeaker.Common.dispatchEvent("onReady",b)})},b.ReadSpeaker.Common.addEvent("onReady",function(){E.executeCode();E.loadExternal();E.flush()}),v?c():b.ReadSpeaker.Common.addEvent("onDOMReady",
c))},Q=function(){rspkr.log("[rspkr.updateBaseClass] Attempting to update..");for(var a=document.getElementsByTagName("div"),d=/\brsbtn\b/,c=0,e=a.length;c<e;c++)d.test(a[c].className)&&(a[c].className=a[c].className.replace(d,b.rsConf.ui.rsbtnClass));rspkr.log("[rspkr.updateBaseClass] Update successful!");P("skinfile")},z={extract:function(a){if("string"==typeof a){for(var b={},a=a.split(/[;&]/),c,e=0;e<a.length;e++)(c=a[e].split("="))&&2==c.length&&(b[unescape(c[0])]=unescape(c[1]).replace(/\+/g,
" "));return b}return{}}},E={isok:!0,executeCode:function(){this.isok=!0;if(!l.length)return!0;for(idx in l)if(l.hasOwnProperty(idx)&&"function"==typeof l[idx])try{l[idx].apply(b,[])}catch(a){this.isok=!1,rspkr.log("[rspkr.q] "+a,3)}},loadExternal:function(){this.isok=!0;if(!q.length)return!0;for(idx in q)if(q.hasOwnProperty(idx))try{n.load(q[idx])}catch(a){this.isok=!1}},flush:function(){l=[];q=[]}},n={load:function(a){if("text/javascript"==a.type||"text/css"==a.type){a.src=w.path+a.src;var d=document.getElementsByTagName("head")[0],
c=document.createElement("text/javascript"==a.type?"script":"link"),e=[f.major,f.minor,f.update,f.revision].join(".");"function"==typeof a.cb&&(void 0!==c.onreadystatechange?c.onreadystatechange=function(){("complete"==this.readyState||"loaded"==this.readyState)&&a.cb.apply(b)}:c.onload=a.cb);c.id=a.id.replace(".","_");c.type=a.type;"text/javascript"==a.type?(c.src=a.src+"?v="+e,a.async&&(c.async=!0)):(c.rel="stylesheet",c.href=a.src+"?v="+e);d.appendChild(c)}}},R=function(a,b){return{id:b[1]||"readspeaker"+
K++,type:b[2]||"text/javascript",src:a,cb:b[3]||null}},U=function(a){v?n.load(R(a,arguments)):q.push(R(a,arguments))},s=0,F={1:[],2:[],3:[],4:[],5:[]},S=function(a){rspkr.log("[rspkr.printErrorLog]",1);for(var a=(a||"3").split(","),d=0;d<a.length;d++)if(F.hasOwnProperty(a[d])){var c=F[a[d]],e=a[d],g="";"1"===e?g="Info":"2"===e?g="Warning":"3"===e?g="Error":"4"===e?g="Andreas":"5"===e&&(g="Anton");console.groupCollapsed&&console.groupCollapsed(g);for(var p=0;p<c.length;p++)try{"2"===e&&console.warn?
console.warn(g+": "+c[p]):"3"===e&&console.error?console.error(g+": "+c[p]):console.log(g+": "+c[p])}catch(f){document.getElementById("readspeaker_debug")?document.getElementById("readspeaker_debug").innerHTML+="<p>"+g+": "+c[p]+"</p>":b.status+=g+": "+c[p]+" "}console.groupCollapsed&&console.groupEnd()}},r=function(a,d){var c=N,d=d||1;F[d].push(a);if(c&&"string"===typeof c&&-1<c.indexOf(","+d+",")){c="";1===d?c="Info":2===d?c="Warning":3===d?c="Error":4===d?c="Andreas":5===d&&(c="Anton");try{2===
d&&console.warn?console.warn(s++ +". "+c+": "+a):3===d&&console.error?console.error(s++ +". "+c+": "+a):console.log(s++ +". "+c+": "+a)}catch(e){document.getElementById("readspeaker_debug")?document.getElementById("readspeaker_debug").innerHTML+="<p>"+s++ +". "+c+": "+a+"</p>":b.status+=s++ +". "+c+": "+a+" "}}};Object.size=function(a){var b=0,c;for(c in a)a.hasOwnProperty(c)&&b++;return b};if(b.rsConf&&b.rsConf.params&&"string"===typeof b.rsConf.params&&b.rsConf.params)var A=b.rsConf.params,i=A.split("?");
else i=document.getElementsByTagName("script"),A=i[i.length-1].getAttribute("src"),i=A.split("?");if(/\?/i.test(A)&&1<i.length&&i[1].length){var m;if(/rsdebug=rsdebug/i.test(document.location.href))try{m=","+document.location.href.split("?").pop().match(/rsdebug=rsdebug([^$|&]*)/i).pop()+","}catch(V){m=",3,"}else m="";N=m;m="";w=z=z.extract(i[1]);j=z.skin||"default";x=z.pids.split(",");w.path=i[0].replace("ReadSpeaker.js","");h.Core=["Common","lib.Facade","modmap"];h["pub.Config"]=!1;document.attachEvent&&
/MSIE/i.test(navigator.userAgent)&&(document.compatMode&&"backcompat"===document.compatMode.toLowerCase()||/MSIE 6\./i.test(navigator.userAgent))?(O=!0,n.load({id:"rsmod_Styles",type:"text/css",src:"ReadSpeaker.Styles-Basic.css",cb:null})):(n.load({id:"rsmod_Styles",type:"text/css",src:"ReadSpeaker.Styles.css",cb:null}),"default"!==j&&(t++,n.load({id:"rsskin_"+j+"_style",type:"text/css",src:"skins/"+j+"/"+j+".css",cb:null}),n.load({id:"rsskin_"+j+"_js",type:"text/javascript",src:"skins/"+j+"/"+j+
".js",cb:function(){"default"!==j&&B?Q():L=!0},async:!0})));for(e in h)h.hasOwnProperty(e)&&(m=e,n.load({id:"req_"+m,type:"text/javascript",src:"ReadSpeaker."+m+".js",cb:function(){var a=(b.event?b.event.srcElement.id:this.id).replace("req_",""),a=a.replace("_","."),a=!1===h[a]?[a]:h[a],d;G++;for(var c=0,e=a.length;c<e;c++)u.push(a[c]),d=D(a[c]),"function"==typeof d.init&&d.init.apply(d,[]);G==Object.size(h)&&(b.ReadSpeaker.Common.addEvent("onModsLoaded",b.ReadSpeaker.pub.Config.setup),M=!0,a={id:"",
type:"text/javascript",src:"",cb:function(){var a=(b.event?b.event.srcElement.id:this.id).replace("rsmod_","");u.push(a);a=D(a);"function"==typeof a.init&&a.init.apply(a,[]);if(M&&b.ReadSpeaker.modmap&&!J){for(var c=b.ReadSpeaker.modmap,a="|",e=[],d="",f="",j=[],h=0,i=x.length;h<i;h++)if(e=c.products&&"function"==typeof c.products[x[h]]?c.products[x[h]]():null)for(var k=0,m=e.length;k<m;k++)d=e[k],f=d[0]+","+d[1]+"|",2<d.length&&(j[d[0]]=d[2]),-1==a.indexOf("|"+f)&&(a+=f);a=a.split("|");k=c=0;for(i=
a.length;k<i;k++)d=a[k].split(","),"undefined"!=typeof d[0]&&/text\/javascript/.test(d[1])&&c++;t+=c;for(var l,k=0,i=a.length;k<i;k++)d=a[k].split(","),d[0].length&&(/text\/javascript/.test(d[1])&&(l=function(){var a=b.event?b.event.srcElement.id:this.id,c=j[a.replace("rsmod_","")];P(a.replace("rsmod_",""),c)}),n.load({id:"rsmod_"+d[0],type:d[1],src:"ReadSpeaker."+d[0]+("text/css"==d[1]?".css":".js"),cb:l,async:!0}));H=!0}}},d=b.ReadSpeaker.lib.Facade.currentLib().toLowerCase(),"rslib"==d?(a.id="rsmod_lib.RSLib",
a.src="ReadSpeaker.lib.RSLib.js"):(a.id="rsmod_lib.Facade.adapter."+d,a.src="ReadSpeaker.lib.Facade.adapter."+d+".js"),n.load(a))},async:!0}))}else J=!0;e=new function(){this.meta={obj:f,version:[f.major,f.minor,f.update].join(".")+"_rev"+f.revision+"-"+f.prod};this.q=function(a){"function"==typeof a&&(C.onReady?a.apply(b,[]):l.push(a))};this.init=function(){B||(B=!0,document.addEventListener&&document.removeEventListener("DOMContentLoaded",b.ReadSpeaker.init,!1),v=!0,b.ReadSpeaker.Common&&b.ReadSpeaker.Common.dispatchEvent("onDOMReady"),
r("[rspkr] DOM Ready!"),L&&(r("[rspkr] Updating base class.",1),Q()))};this.dynload=U;this.getLoadedMods=function(){return u};this.rsidCount=1E3;this.logcount=0;this.log=function(a,b){r(a,b||1)};this.showLog=function(a){S(a||"1")};this.showLog=function(a){S(a||"1")};this.getID=function(){return"readspeaker"+K++};this.getVersion=function(){return this.meta.version};this.s=T;this.skin=j;this.displog=C;this.basicMode=O;this.params=w};b.ReadSpeaker=b.rs=b.rspkr=e})(window);
ReadSpeaker.enums={mime:{tjs:"text/javascript",tcss:"text/css",thtml:"text/html"}};(function(b){var e=navigator.userAgent,f=eval("/*@cc_on! @*/false"),h=setTimeout;/mozilla/i.test(e)&&!/(compati)/.test(e)||/opera/i.test(e)||/webkit/i.test(e)?document.addEventListener("DOMContentLoaded",b,!1):f?function(){var e=document.createElement("doc:rdy");try{e.doScroll("left"),b()}catch(f){h(arguments.callee,0)}}():window.onload=b})(ReadSpeaker.init);
