ReadSpeaker.ui = (function () {
  var a = null,
    c = [],
    j = [],
    r = !1,
    m = function () {
      rspkr.log("[rspkr.ui] Attempting to add click events.");
      var a = $rs.get("." + rspkr.ui.rsbtnClass + " a.rsbtn_play"),
        b = null;
      $rs.isArray(a) || (a = [a]);
      for (var c = 0, d = a.length; c < d; c++)
        $rs.unregEvent(a[c], "click", ReadSpeakerDefer.clickhandler),
          (b = a[c] ? $rs.getAttr(a[c], "data-rsevent-id") : "_bogus_"),
          rspkr.l.f.eq.store[b] && rspkr.l.f.eq.store[b].click
            ? rspkr.log("[rspkr.ui] Click event already existed on " + a[c], 2)
            : ($rs.regEvent(a[c], "click", function (g) {
              window.readpage(this);
              if ((g = g.originalEvent)) (g.cancelBubble = !0), g.preventDefault && g.preventDefault(), g.stopPropagation && g.stopPropagation(), (g.returnValue = !1);
              return !1;
            }),
              rspkr.ui.addFocusHandler(a[c], !0, a[c].parentNode),
              rspkr.log("[rspkr.ui] Added click event to: " + a[c], 1));
    },
    k = function () {
      rspkr.log("[rspkr.ui] Initiating global callbacks");
      rspkr.ui.rsbtnClass = rspkr.cfg.item("ui.rsbtnClass") || "rsbtn";
      window.readpage = function (a, b) {
        rspkr.ui.initrun && rspkr.ui.showPlayer(a, b);
      };
      window.rshlexit = function (b) {
        (void 0 === b || "false" === b) && a.stop();
      };
      window.rshlinit = p().sync.init;
      window.rshlsetContent = p().sync.setContent;
      window.rshlsetId = p().sync.setId;
      window.rshlsync = function (a, b) {
        for (var t = a.split(","), g = b.split(","), h = 0, c = a.length; h < c; h++) p().sync.execute(t[h], g[h]);
      };
      var b = rspkr.c.data.browser;
      b && (/iphone|ipad|ios|android/i.test(b.OS) || "android" == b.name.toLowerCase())
        ? $rs.regEvent(document.body, "touchstart", function (a) {
          rspkr.c.data.setSelectedText(a);
          return !0;
        })
        : ($rs.regEvent(document.body, "mousedown", function (a) {
          rspkr.ui.setPointerPos(a);
          return !0;
        }),
          $rs.regEvent(document.body, "mouseup", function (a) {
            "opera" === b.name.toLowerCase()
              ? setTimeout(function () {
                rspkr.c.data.setSelectedText(a);
              }, 50)
              : rspkr.c.data.setSelectedText(a);
            return !0;
          }),
          $rs.regEvent(window, "mouseup", function (a) {
            "opera" === b.name.toLowerCase()
              ? setTimeout(function () {
                rspkr.c.data.setSelectedText(a);
              }, 50)
              : rspkr.c.data.setSelectedText(a);
            return !0;
          }),
          $rs.regEvent(document.body, "keydown", rspkr.ui.setPointerPos),
          $rs.regEvent(document.body, "keyup", function (a) {
            rspkr.c.data.setSelectedText(a);
            return !0;
          }));
    },
    s = function () {
      document.removeEventListener ? document.removeEventListener("click", window.ReadSpeakerDefer.clickhandler, !1) : document.detachEvent && document.detachEvent("onclick", window.ReadSpeakerDefer.clickhandler);
      if (ReadSpeakerDefer.deferred) {
        var a = ReadSpeakerDefer.deferred,
          b = null;
        if ("a" != a.tagName.toLowerCase()) {
          for (b = a; "body" != b.tagName.toLowerCase() && !((b = b.parentNode), "a" == b.tagName.toLowerCase()););
          a = b;
        }
        ReadSpeakerDefer.isRSLink(a) && (rspkr.log("[rspkr.ui] Activating deferred element: " + a), $rs.removeClass(a.parentNode, "rsdeferred"), rspkr.ui.showPlayer(a));
        ReadSpeakerDefer.deferred = null;
      }
    },
    e = null,
    q = function () {
      e && (rspkr.log("[rspkr.ui.updateFocus] " + e.outerHTML), d(e));
    },
    d = function (a) {
      $rs.focus && "function" == typeof $rs.focus && a && $rs.focus(a);
    },
    f = function (a) {
      if ("iconon" == rspkr.st.get("hlicon") && !r) {
        var c = j.push(new b()) - 1;
        j[c].id = c;
        j[c].show(a);
        r = !0;
      }
    },
    i = function () {
      "iconon" == rspkr.st.get("hlicon") && r && (j.pop().hide(), (r = !1));
    },
    b = function () {
      var a = 0,
        b = 0,
        c = null,
        d = 52,
        g = null,
        h = null,
        l = null,
        e = function (a) {
          a = a || c;
          $rs.addClass(a, rspkr.ui.rsbtnClass + " rspopup");
          rspkr.cfg.item("general.useCompactPopupButton") && $rs.addClass(a, "rscompact");
        },
        n = function (a) {
          $rs.unregEvent(c, "mouseout", f);
          window.clearTimeout(g);
          var b,
            t = c.clientWidth + 10,
            d;
          h = rspkr.ui.showPlayer(l, c, !0);
          d = h.getWidth();
          b = parseInt($rs.offset(c).left);
          if ((b = rspkr.ui.viewport.width + $rs.scrollLeft(document) - b) < d) (b = parseInt($rs.css(c, "left")) - (d - (t - 10))), $rs.css(c, "left", b + "px");
          r = !1;
          $rs.unregEvent(l, "click", n);
          $rs.regEvent(l, "click", function (a) {
            a.originalEvent && a.originalEvent.preventDefault && a.originalEvent.preventDefault();
            a.originalEvent.returnValue = !1;
            return h.restart();
          });
          a.originalEvent && a.originalEvent.preventDefault && a.originalEvent.preventDefault();
          return (a.originalEvent.returnValue = !1);
        },
        f = function () {
          g ||
            (g = window.setTimeout(function () {
              i();
            }, rspkr.cfg.item("general.popupCloseTime") || 2e3));
        },
        p = function () {
          g && (window.clearTimeout(g), (g = null));
        },
        k = function (a, b) {
          var g = $rs.offset(document.body);
          $rs.css(c, { top: b - g.top + "px", left: a - g.left + "px", width: d + "px" });
        },
        i = function () {
          $rs.css(c, { display: "none", top: 0, left: 0 });
          p();
          j.splice(null, 1);
          r = !1;
          c.parentElement.removeChild(c);
        },
        m = rspkr.c.findFirstRSButton(),
        c = document.createElement("div");
      c.id = rspkr.getID();
      c.innerHTML = rspkr.cfg.item("ui.popupbutton").join("");
      e();
      l = $rs.findIn(c, "a.rsbtn_play");
      l.href = m ? m.href : null;
      m || (l.href = rspkr.cfg.item("general.popupHref"));
      var m = l.href.match(/lang=([^&;]*)/i).pop(),
        q = $rs.findIn($rs.get(c), "a.rsbtn_play span.rsbtn_text span");
      q && (q.textContent = q.innerText = rspkr.cfg.getPhrase("listen", m, "en_us"));
      $rs.setAttr(l, "title", rspkr.cfg.getPhrase("listentoselectedtext", m, "en_us"));
      $rs.regEvent(l, "click", n);
      document.body.appendChild(c);
      return {
        setPos: k,
        show: function (g) {
          p(g);
          if (g && "none" == $rs.css(c, "display")) {
            var h = c.cloneNode(!0);
            h.id = rspkr.getID();
            $rs.css(h, { display: "block", position: "absolute", top: 0, left: 0 });
            document.body.appendChild(h);
            d = $rs.outerWidth(h) + 3;
            document.body.removeChild(h);
            h = g.pageX;
            g = g.pageY;
            b = g > rspkr.ui.pointerY ? (g - $rs.scrollTop(document) + 36 > rspkr.ui.viewport.height - 46 ? g - 56 : g + 20) : 10 > g - $rs.scrollTop(document) - 56 ? g + 20 : g - 56;
            a = 10 > h - $rs.scrollLeft(document) ? h + 10 : h - $rs.scrollLeft(document) > rspkr.ui.viewport.width - (d + 10) ? rspkr.ui.viewport.width + $rs.scrollLeft(document) - (d + 10) : h + 0;
            k(a, b);
          }
          $rs.regEvent(c, "mouseout", f);
          $rs.regEvent(c, "mouseover", p);
          f(null);
          e();
          $rs.css(c, "display", "block");
        },
        hide: i,
        id: null,
      };
    },
    l = {
      update: function (b, c, d) {
        "hlspeed" === b && c !== d && ((b = b.replace("hl", "")), rspkr.c.converter[b] && "function" == typeof rspkr.c.converter[b] && (c = rspkr.c.converter[b](c)), (rspkr.c.data[b] = c), a.stop(), rspkr.pl.releaseAdapter());
      },
    },
    n = function (a, b, c, d, g, h) {
      $rs.css(a, "background-color", "rgb(" + b + "," + c + "," + d + ")");
      d < g
        ? ((d += 10),
          window.setTimeout(function () {
            n(a, b, c, d, g, h);
          }, 50))
        : h && "function" === typeof h && h.apply(a, []);
    },
    p = function () {
      return rspkr.XP ? rspkr.XP : rspkr.HL;
    };
  return {
    meta: { revision: "1728" },
    initrun: !1,
    init: function () {
      evt = rspkr.Common.addEvent;
      ui = rspkr.ui;
      evt("onAfterModsLoaded", k);
      evt("onReady", m);
      evt("onReady", s);
      evt("onSelectedText", f);
      evt("onDeselectedText", i);
      evt("onSettingsChanged", l.update);
      evt("onAfterSyncInit", q);
      this.initrun = !0;
      rspkr.Common.dispatchEvent("onUIInitialized");
      rspkr.log("[rspkr.ui] Initialized!");
    },
    addFocusHandler: function (a, b, c) {
      var d = b,
        g = c,
        g = g || a;
      void 0 === d && (d = !0);
      $rs.focusIn &&
        "function" == typeof $rs.focusIn &&
        ($rs.focusIn(a, function () {
          $rs.addClass(g, "rsfocus");
          !0 === d && (e = a);
          rspkr.Common.dispatchEvent("onFocusIn", window, [a, g]);
        }),
          $rs.focusOut(a, function () {
            $rs.removeClass(g, "rsfocus");
            rspkr.Common.dispatchEvent("onFocusOut", window, [a, g]);
          }));
    },
    focus: function (a) {
      d(a);
    },
    updateFocus: function () {
      q();
    },
    showOverlay: function (b, c) {
      var d = b,
        l;
      l = c || a.getContainer();
      var g = $rs.findIn(l, ".rsbtn_status");
      0 === g.length &&
        ((g = document.createElement("span")), (g.className = "rsbtn_status_overlay"), (g.innerHTML = '<span class="rsbtn_status"></span>'), $rs.findIn(l, ".rsbtn_exp").appendChild(g), (g = $rs.findIn(l, ".rsbtn_status")));
      "nosound" === d
        ? ((d = '<a class="rsbtn_nosound">' + rspkr.cfg.getPhrase("nosound") + "</a>"),
          (g.innerHTML = d),
          (d = $rs.findIn(l, ".rsbtn_nosound")) &&
          $rs.regEvent(d, "click", function () {
            return a.nosound();
          }))
        : (g.innerHTML = d);
    },
    settings: l,
    rsbtnClass: "",
    addClickEvents: function () {
      m();
    },
    initGlobalCallbacks: function () {
      k();
    },
    showPopupIcon: function (a) {
      f(a);
    },
    processDeferred: function () {
      s();
    },
    showPlayer: function (b, d, l) {
      var e;
      rspkr.log("[rspkr.ui.showPlayer]");
      var l = l || !1,
        g;
      if ("string" == typeof b)
        b: {
          g = $rs.get("a");
          for (var h = 0, f = g.length; h < f; h++)
            if (g[h].href && g[h].href == b) {
              g = g[h];
              break b;
            }
          g = !1;
        }
      else g = b;
      b = "string" == typeof b ? b : g.href;
      h = null;
      rspkr.c.data.setParams(b);
      d && !l
        ? ((h = $rs.get(d)), $rs.addClass(h, rspkr.ui.rsbtnClass + " rsfloating"), rspkr.basicMode && ($rs.removeClass(h, "rshidden"), $rs.addClass(h, rspkr.ui.rsbtnClass + " rsvisible")))
        : (h = $rs.closest(g, "div." + rspkr.ui.rsbtnClass));
      if (rspkr.cfg.item("survey.allowed") && "1" === rspkr.c.cookie.readKey(rspkr.cfg.item("general.cookieName"), "nmbrdisplays"))
        rspkr.ui.Lightbox.show(rspkr.cfg.item("survey.url"), rspkr.cfg.item("ui.survey.buttons").join(), !0), (e = void 0);
      else {
        b: {
          d = h;
          for (e in c)
            if (c[e] && c[e].getContainer && c[e].getContainer() == d) {
              e = c[e];
              break b;
            }
          e = new rspkr.ui.Player(d);
          c.push(e);
        }
        if ((a && a != e) || (a && b !== a.getHref())) a.close(!0), rspkr.c.dispatchEvent("onUIClosePlayer", a.getContainer(), [0 < rspkr.c.data.selectedText.length ? "textsel" : "nosel"]);
        d = (d = a) ? d.getID() : null;
        rspkr.c.dispatchEvent("onUIShowPlayer", window, [d, e.getID()]);
        e.setHref(b);
        e.show();
        e = a = e;
      }
      return e;
    },
    pointerX: 0,
    pointerY: 0,
    setPointerPos: function (a) {
      rspkr.ui.pointerX = a.pageX;
      rspkr.ui.pointerY = a.pageY;
      return !0;
    },
    viewport: { width: $rs.width(window), height: $rs.height(window) },
    popups: j,
    hl: function (a, b) {
      window.setTimeout(function () {
        n(a, 255, 255, 100, 255, b);
      }, 200);
    },
    scroll: {
      INTERVAL: null,
      STEPS: 25,
      scrollToElm: function (a) {
        $rs.isVisible(a) && this.initScroll(a);
      },
      scrollToAnchor: function (a) {
        for (var b = $rs.get("a"), c = null, d = 0; d < b.length; d++) {
          var g = b[d];
          if (g.name && g.name == a) {
            c = g;
            break;
          }
        }
        this.initScroll(c);
      },
      initScroll: function (a) {
        if (a) {
          for (var b = a.offsetTop, c = a; c.offsetParent && c.offsetParent != document.body;) (c = c.offsetParent), (b += c.offsetTop);
          b -= 50;
          clearInterval(rspkr.u.scroll.INTERVAL);
          var c = rspkr.u.scroll.getCurrentYPos(),
            d = parseInt((b - c) / rspkr.u.scroll.STEPS);
          rspkr.u.scroll.INTERVAL = setInterval(function () {
            rspkr.u.scroll.scrollWindow(d, b, a);
          }, 10);
        } else document.location.hash = a;
      },
      getCurrentYPos: function () {
        return document.body && document.body.scrollTop ? document.body.scrollTop : document.documentElement && document.documentElement.scrollTop ? document.documentElement.scrollTop : window.pageYOffset ? window.pageYOffset : 0;
      },
      scrollWindow: function (a, b, c) {
        var d = rspkr.u.scroll.getCurrentYPos(),
          g = d < b;
        window.scrollTo(0, d + a);
        a = rspkr.u.scroll.getCurrentYPos();
        if (g != a < b || d == a) window.scrollTo(0, b), clearInterval(rspkr.u.scroll.INTERVAL), "string" == typeof c && (location.hash = c);
      },
    },
    activePlayer: a,
    getActivePlayer: function () {
      return a;
    },
  };
})();
ReadSpeaker.ui.Slider = function () {
  var a = this,
    c = { handleClass: "", width: 0, height: 0, left: 0, top: 0, steps: -1, stepsize: -1, dir: "h", initval: -1, drop: null, start: null, dragging: null, click: null, labelDragHandle: "", labelStart: "", labelEnd: "" },
    j = { rsid: void 0, parent: void 0, ref: void 0 },
    r = 5,
    m = void 0,
    k = void 0,
    s = void 0,
    e = void 0,
    q = void 0,
    d = void 0,
    f = void 0,
    i = !1;
  this.initElement = function (a) {
    if (!i) {
      "string" == typeof a && (a = document.getElementById(a));
      a.innerHTML += '<input role="slider" class="keyLink" style="display:block; border:0;">&nbsp;</input>';
      var d = a.getElementsByTagName("input"),
        d = d[d.length - 1],
        e = -1 < c.steps ? c.steps : 100;
      d.relatedElement = a;
      $rs.setAttr(d, "title", c.labelDragHandle);
      $rs.setAttr(d, "aria-label", c.labelDragHandle);
      $rs.setAttr(d, "aria-orientation", "h" == c.dir ? "horizontal" : "vertical");
      $rs.setAttr(d, "aria-valuemin", 0);
      $rs.setAttr(d, "aria-valuemax", e);
      $rs.setAttr(d, "aria-valuenow", c.initval || 0);
      $rs.regEvent(a, "mousedown", this.startDragMouse);
      $rs.regEvent(d, "keyup", this.startDragKeys);
      $rs.regEvent(d, "dragstart", function (a) {
        a.originalEvent && a.originalEvent.preventDefault && a.originalEvent.preventDefault();
        return (a.originalEvent.returnValue = !1);
      });
      $rs.regEvent(a, "touchstart", this.touchStart);
      $rs.regEvent(j.parent, "mousedown", this.mouseClick);
    }
  };
  this.mouseClick = function (b) {
    if (!i && !$rs.hasClass(j.ref, "dragged")) {
      var d = a.findPos(b.target),
        f = b.clientX - (d.left - c.left),
        b = b.clientY - (d.top - c.top);
      s = d.left;
      e = d.top;
      d = a.getCurrentVal({ left: f, top: b });
      "function" == typeof c.click && c.click(d, j);
      return !1;
    }
  };
  this.findPos = function (a) {
    var d = (curTop = 0);
    if (a.offsetParent) {
      do (d += a.offsetLeft), (curTop += a.offsetTop);
      while ((a = a.offsetParent));
      return { left: d, top: curTop };
    }
  };
  this.startDragMouse = function (b) {
    rspkr.log("[rspkr.ui.Slider] startDragMouse");
    if (!i) {
      a.startDrag(this);
      var d = b || window.event;
      m = d.clientX;
      k = d.clientY;
      $rs.regEvent(document.body, "mousemove", a.dragMouse);
      $rs.regEvent(document.body, "mouseup", a.releaseElement);
    }
    b.preventDefault && b.preventDefault();
    return !1;
  };
  this.startDragKeys = function (b) {
    b = b || window.event;
    rspkr.log("[rspkr.ui.Slider] startDragKeys " + b.keyCode);
    13 == b.keyCode &&
      !i &&
      (a.startDrag(this.relatedElement), (q = d = 0), $rs.regEvent(document.body, "keydown", a.dragKeys), $rs.regEvent(document.body, "keypress", a.switchKeyEvents), $rs.addClass(this.relatedElement, "rskeycontrolled"));
    b.preventDefault && b.preventDefault();
    return (b.returnValue = !1);
  };
  this.touchStart = function (b) {
    b = b.originalEvent;
    rspkr.log("[rspkr.ui.Slider] touchStart");
    i || (a.startDrag(b.target), (m = b.touches[0].pageX), (k = b.touches[0].pageY), $rs.regEvent(b.target, "touchmove", a.touchMove), $rs.regEvent(b.target, "touchend", a.releaseElement));
    return !1;
  };
  this.startDrag = function (b) {
    rspkr.log("[rspkr.ui.Slider] startDrag");
    f && a.releaseElement();
    s = b.offsetLeft;
    e = b.offsetTop;
    f = b;
    $rs.addClass(f, "dragged");
    "function" == typeof c.start && c.start(j);
  };
  this.dragMouse = function (b) {
    b = b || window.event;
    a.setPosition(b.clientX - m, b.clientY - k);
    a.valueChanged = !0;
    return !1;
  };
  this.touchMove = function (b) {
    b = b.originalEvent;
    b.preventDefault();
    a.setPosition(b.touches[0].pageX - m, b.touches[0].pageY - k);
    a.valueChanged = !0;
    return !1;
  };
  this.dragKeys = function (b) {
    b = b || window.event;
    switch (b.keyCode) {
      case 37:
      case 63234:
        a.valueChanged = !0;
        q -= r;
        break;
      case 38:
      case 63232:
        a.valueChanged = !0;
        d -= r;
        break;
      case 39:
      case 63235:
        a.valueChanged = !0;
        q += r;
        break;
      case 40:
      case 63233:
        a.valueChanged = !0;
        d += r;
        break;
      case 13:
      case 27:
        return a.releaseElement(), !1;
      case 9:
        return a.releaseElement(), !0;
      default:
        return rspkr.log("[rspkr.ui.Slider] return TRUE"), !0;
    }
    !0 === a.valueChanged && (rspkr.c.dispatchEvent("onUISliderMove"), a.setPosition(q, d));
    b.originalEvent && b.originalEvent.preventDefault && b.originalEvent.preventDefault();
    b.returnValue = !1;
    rspkr.log("[rspkr.ui.Slider] ready to return!");
    return !1;
  };
  this.setPosition = function (b, d) {
    var n,
      p = !1;
    n = b;
    var k = s,
      i = c.left,
      m = c.width,
      q = "left";
    "v" == c.dir && ((n = d), (k = e), (i = c.top), (m = c.height), (q = "top"));
    n = k + n;
    -1 < c.stepsize && ((n + i) % c.stepsize ? (n = c.stepsize * Math.ceil(n / c.stepsize) + i) : (p = !0));
    n > m + i ? (n = m + i) : n < i && (n = i);
    p || ((f.style[q] = n + "px"), "function" == typeof c.dragging && c.dragging(a.getCurrentVal(), j));
  };
  this.switchKeyEvents = function () {
    $rs.unregEvent(document.body, "keydown", a.dragKeys);
    $rs.unregEvent(document.body, "keypress", a.switchKeyEvents);
    $rs.regEvent(document.body, "keypress", a.dragKeys);
  };
  this.releaseElement = function () {
    rspkr.log("[rspkr.ui.Slider] releaseElement");
    $rs.unregEvent(document.body, "mousemove", a.dragMouse);
    $rs.unregEvent(document.body, "mouseup", a.releaseElement);
    $rs.unregEvent(document.body, "keypress", a.dragKeys);
    $rs.unregEvent(document.body, "keypress", a.switchKeyEvents);
    $rs.unregEvent(document.body, "keydown", a.dragKeys);
    $rs.unregEvent(f, "touchmove", a.touchMove);
    $rs.unregEvent(f, "touchend", a.releaseElement);
    $rs.removeClass(f, "dragged");
    $rs.removeClass(f, "rskeycontrolled");
    $rs.removeClass(f, "rsmousecontrolled");
    var b = a.getCurrentVal();
    f = null;
    "function" == typeof c.drop && !0 === a.valueChanged && c.drop(b, j);
    return (a.valueChanged = !1);
  };
  this.getCurrentVal = function (a) {
    var d = c.width,
      e = "left",
      f = c.left;
    "v" == c.dir && ((d = c.height), (e = "top"), (f = c.top));
    var i = -1 < c.steps ? c.steps : 100,
      d = -1 < c.stepsize ? c.stepsize : d / i,
      a = a ? a[e] : $rs.css(j.ref, e).replace(/px/i, "");
    pos = Math.round(a) - f;
    a = Math.round(pos / d);
    "v" == c.dir && (a = i - a);
    rspkr.log("[rspkr.ui.Slider] currentval: " + a);
    return a;
  };
  return {
    init: function (b, d) {
      "string" == typeof b && (b = document.getElementById(b));
      if (b) {
        var e = b.id || "data-readspeaker-slider-id-" + Math.floor(2e4 * Math.random());
        b.setAttribute && b.setAttribute("data-readspeaker-slider-id-", "data-readspeaker-slider-parent-" + e);
        var f = {
          width: function () {
            return $rs.width(b);
          },
          height: function () {
            return $rs.height(b);
          },
        };
        if ("object" == typeof d) for (var i in d) d.hasOwnProperty(i) && void 0 !== c[i] && (c[i] = d[i]);
        i = !1;
        var k;
        "rsbtn_volume_slider" === b.className && "jquery" === rspkr.l.f.currentLib() && 1.5 > parseFloat(jQuery.fn.jquery) && ((k = b.parentNode.style.display), (b.parentNode.style.display = "block"), (i = !0));
        c.width = f.width();
        c.height = f.height();
        i && (b.parentNode.style.display = k);
        -1 < c.steps && (c.stepsize = ("h" == c.dir ? c.width : c.height) / c.steps);
        f = document.createElement("span");
        f.setAttribute("data-readspeaker-slider-id-", e);
        f.className = c.handleClass || "rsbtn_progress_handle rsimg";
        b.appendChild(f);
        j.rsid = e;
        j.parent = b;
        j.ref = f;
        r = -1 < c.stepsize ? c.stepsize : r;
        e = $rs.css(f, "left");
        null !== e && (c.left = parseInt(e.replace(/px/i, "")));
        e = $rs.css(f, "top");
        null !== e && (c.top = parseInt(e.replace(/px/i, "")));
        -1 < c.initval && this.jumpTo(c.initval);
        c.labelStart && ((e = document.createElement("span")), (e.className = "slider-label-start"), (e.innerHTML = c.labelStart), b.appendChild(e));
        c.labelEnd && ((e = document.createElement("span")), (e.className = "slider-label-end"), (e.innerHTML = c.labelEnd), b.appendChild(e));
        a.initElement(f);
      }
    },
    jumpTo: function (a) {
      if (isNaN(a)) return !1;
      var d = 101,
        e = a;
      -1 < c.steps && ((a = Math.round(a)), (d = c.steps + 1));
      if (-1 < a && a < d) {
        var f = c.width,
          i = c.left,
          k = "left";
        "v" == c.dir && ((f = c.height), (i = c.top), (k = "top"), (a = d - 1 - a));
        j.ref.style[k] = (f / (d - 1)) * a + i + "px";
        $rs.setAttr($rs.findIn(j.ref, "input.keyLink"), "aria-valuenow", e);
      }
    },
    getInstance: function () {
      return j;
    },
    getContainer: function () {
      return j.parent;
    },
    getAttr: function (a) {
      return $rs.getAttr(j.parent, "data-readspeaker-" + a);
    },
    setAttr: function (a, d) {
      $rs.setAttr(j.parent, "data-readspeaker-" + a, d);
    },
    releaseElement: function () {
      a.releaseElement();
    },
    startDragKeys: function (d, c) {
      a.startDragKeys.call(d, c);
    },
    disabled: function () {
      if (arguments) i = arguments[0];
      else return i;
    },
  };
};
ReadSpeaker.ui.Player = function (a) {
  var c = rspkr.getID(),
    j = this,
    r = [],
    m = 0,
    k = !1,
    s = null,
    e = {
      _play: null,
      _pause: null,
      _stop: null,
      _vol: null,
      _settings: null,
      _dl: null,
      _closer: null,
      _powered: null,
      _get: function (g, d) {
        var b,
          g = "_" + g;
        b = a ? (this[g] && 0 < this[g].length ? this[g] : (this[g] = $rs.findIn(a, d))) : null;
        return b == [] ? null : b;
      },
      play: function () {
        return this._get("play", ".rsbtn_play");
      },
      pause: function () {
        return this._get("pause", ".rsbtn_pause");
      },
      stop: function () {
        return this._get("stop", ".rsbtn_stop");
      },
      vol: function () {
        return this._get("vol", ".rsbtn_volume");
      },
      settings: function () {
        return this._get("settings", ".rsbtn_settings");
      },
      dl: function () {
        return this._get("dl", ".rsbtn_dl");
      },
      powered: function () {
        return this._get("powered", ".rsbtn_powered");
      },
      closer: function () {
        return this._get("closer", ".rsbtn_closer");
      },
      nosound: function () {
        return this._get("nosound", ".rsbtn_nosound");
      },
      setPlayPause: function (a) {
        rspkr.log("[rspkr.ui.Player.setPlayPause(" + a + ")]");
        a = a ? $rs.getAttr(this.pause(), "data-rsphrase-play") : $rs.getAttr(this.pause(), "data-rsphrase-pause");
        $rs.setAttr(this.pause(), "title", rspkr.c.decodeEntities(a));
        $rs.findIn(this.pause(), ".rsbtn_btnlabel").innerHTML = a;
      },
    },
    q = !1,
    d = [],
    f = {
      play: function () {
        rspkr.c.dispatchEvent("onUIBeforePlay");
        rspkr.log("[rspkr.ui.handlers.play]");
        d.progress && d.progress.disabled(!1);
        f.setStateClass(a, "rsplaying");
        rspkr.basicMode && f.setStateClass($rs.findIn(a, ".rsbtn_exp"), "rsplaying");
        $rs.addClass($rs.findIn(a, ".rsbtn_progress_container"), "rsloading");
        e.setPlayPause(!1);
        rspkr.pl.play();
        d.progress &&
          rspkr.c.addEvent("onBeforeSyncInit", function () {
            rspkr.pl.getProgress.apply(rspkr.pl, [!0, b, j]);
          });
        "flash" === rspkr.pl.adapter && !rspkr.displog.onVolumeAdjusted && rspkr.pl.setVolume(parseInt(rspkr.st.get("hlvol") || "100"));
        rspkr.c.dispatchEvent("onUIAfterPlay");
        rspkr.cfg.execCallback("cb.ui.play", a);
      },
      pause: function () {
        rspkr.log("[rspkr.ui.handlers.pause]");
        f.setStateClass(a, "rspaused");
        rspkr.basicMode && f.setStateClass($rs.findIn(a, ".rsbtn_exp"), "rspaused");
        e.setPlayPause(!0);
        rspkr.pl.pause();
        rspkr.pl.getProgress(!1);
        rspkr.c.dispatchEvent("onUIPause");
        rspkr.cfg.execCallback("cb.ui.pause", a);
        rspkr.log("ReadSpeaker.ui.pause");
      },
      stop: function () {
        rspkr.log("[rspkr.ui.handlers.stop]");
        d.progress && d.progress.disabled(!0);
        f.setStateClass(a, "rsstopped");
        $rs.removeClass($rs.findIn(a, ".rsbtn_progress_container"), "rsloading");
        rspkr.basicMode && f.setStateClass($rs.findIn(a, ".rsbtn_exp"), "rsstopped");
        e.setPlayPause(!0);
        d.progress && (d.progress.jumpTo(0), d.progress.setAttr("current", 0), i(0));
        rspkr.pl.stop();
        rspkr.pl.getProgress(!1);
        rspkr.c.dispatchEvent("onUIStop", a);
        rspkr.cfg.execCallback("cb.ui.stop", a);
        rspkr.log("ReadSpeaker.ui.stop");
      },
      setStateClass: function (a, d) {
        a && ($rs.removeClass(a, "rspaused rsstopped rsplaying"), $rs.addClass(a, d));
      },
      vol: function (b) {
        var c = $rs.findIn(a, ".rsbtn_volume_container"),
          e = $rs.findIn(a, ".rsbtn_volume"),
          b = b.originalEvent,
          f = function (a) {
            var d = a.originalEvent,
              d = $rs.closest(d.srcElement || d.originalTarget, ".rsbtn_volume_container");
            if ("none" === $rs.css(c, "display")) return !1;
            if ("click" === a.type) {
              if (void 0 === d || ($rs.isArray(d) && !d.length)) $rs.css(c, "display", "none"), $rs.unregEvent(document.body, "click", f);
            } else "keyup" === a.type && 27 === a.keyCode && ($rs.css(c, "display", "none"), $rs.unregEvent(document.body, "keyup", f));
          };
        $rs.css(c, "left", e.offsetLeft + "px");
        $rs.css(c, "display", "none" == $rs.css(c, "display") ? "block" : "none");
        "block" === $rs.css(c, "display") && ($rs.regEvent(document.body, "click", f), $rs.regEvent(document.body, "keyup", f));
        b && b.stopPropagation && b.stopPropagation();
        b.cancelBubble = !0;
        e = $rs.findIn(c, ".keyLink");
        d.vol.startDragKeys(e, { keyCode: 13 });
        return !1;
      },
      settings: function () {
        this.pause();
        rspkr.ui.Lightbox.show(rspkr.st.getHTML(), rspkr.st.getButtons(), !0, function (a) {
          rspkr.c.dispatchEvent("onSettingsLoaded", window, []);
          rspkr.cfg.execCallback("cb.ui.settingsopened", a);
        });
      },
      close: function (b) {
        var b = b || !1,
          c = rspkr.pl,
          f = !1;
        b || rspkr.cfg.execCallback("cb.ui.beforeclose", a);
        c.hasOwnProperty("getProgress") && rspkr.pl.getProgress(!1);
        c.hasOwnProperty("releaseAdapter") && rspkr.pl.releaseAdapter();
        d.progress && (d.progress.jumpTo(0), d.progress.setAttr("current", 0));
        $rs.removeClass(a, "rsstopped rsplaying rspaused rsexpanded");
        if (rspkr.basicMode) {
          var i;
          (i = $rs.findIn(a, ".rsbtn_play")) && $rs.removeClass(i, "rsexpanded");
        }
        $rs.hasClass(a, "rsfloating") && ($rs.removeClass(a, rspkr.ui.rsbtnClass), rspkr.basicMode && ($rs.removeClass(a, "rsvisible"), $rs.addClass(a, "rshidden")));
        e.setPlayPause(!0);
        $rs.hasClass(a, "rspopup") && ((f = !0), $rs.removeClass(a, "rspopup"), $rs.css(a, "display", "none"), a.parentNode.removeChild(a));
        $rs.css(a, "width", "auto");
        delete rspkr.displog.onVolumeAdjusted;
        b || (rspkr.c.dispatchEvent("onUIClosePlayer", a, ["userclick"]), rspkr.cfg.execCallback("cb.ui.close", a), rspkr.log("ReadSpeaker.ui.close: " + a));
        !b && !1 === f && rspkr.ui.focus($rs.findIn($rs.get(a), ".rsbtn_play"));
      },
      dl: function () {
        this.pause();
        var a = rspkr.c.data.getSaveData("dialog"),
          d = !1;
        rspkr.log("[rspkr.ui.handlers.dl] Savelink: " + a);
        rspkr.u.Lightbox.show(this.getDlDialog(), this.getDlButtons(), !0, function () {
          var b = $rs.get("#rsdl_button_accept"),
            c = $rs.get("#rsdl_button_decline");
          b &&
            $rs.regEvent(b, "click", function () {
              rspkr.u.Lightbox.hide();
              d = "iOS" !== rspkr.c.data.browser.OS && 0 < rspkr.c.data.selectedHTML.length ? !0 : "iOS" !== rspkr.c.data.browser.OS && !0 === rspkr.cfg.item("general.usePost") ? !0 : !1;
              if (!0 === d) {
                var c = null;
                if (document.getElementById("dliframe")) c = document.getElementById("dliframe");
                else {
                  if (document.selection)
                    try {
                      c = document.createElement('<iframe name="dliframe">');
                    } catch (e) {
                      c = document.createElement("iframe");
                    }
                  else c = document.createElement("iframe");
                  c.name = "dliframe";
                  c.setAttribute("id", "dliframe");
                  c.setAttribute("style", "display: none; position: absolute;");
                  c.style.display = "none";
                  var f = document.getElementsByTagName("body"),
                    i = null;
                  0 < f.length && (i = f.item(0));
                  if (i) i.appendChild(c);
                  else return;
                }
                c.src = a;
                return !1;
              }
              $rs.setAttr(b, "href", a);
              return !0;
            });
          c &&
            ($rs.regEvent(c, "click", rspkr.u.Lightbox.hide),
              setTimeout(function () {
                rspkr.ui.focus(c);
              }, 200));
        });
      },
      getDlDialog: function () {
        var a = rspkr.cfg.item("ui.dldialog").join("\n"),
          d = {};
        d.rsTERMS_OF_USE_HEADINGrs = rspkr.cfg.getPhrase("touheading");
        d.rsTERMS_OF_USE_BODYrs = rspkr.cfg.getPhrase("toubody");
        return rspkr.st.r().replaceTokens(a, d);
      },
      getDlButtons: function () {
        var a = rspkr.cfg.item("ui.dlbuttons").join("\n"),
          d = {};
        d.rsTERMS_OF_USE_ACCEPTrs = rspkr.cfg.getPhrase("touaccept");
        d.rsTERMS_OF_USE_DECLINErs = rspkr.cfg.getPhrase("toudecline");
        return rspkr.st.r().replaceTokens(a, d);
      },
      nosound: function () {
        var a = rspkr.c.data.getSaveData("link");
        $rs.setAttr(e.nosound(), "href", a);
        return !0;
      },
    },
    i = function (d) {
      var d = 100 < d ? 100 : d,
        b = $rs.findIn(a, ".rsbtn_progress_played");
      "object" === typeof b && $rs.css(b, "width", d + "%");
      rspkr.cfg.execCallback("cb.ui.progresschanged", a, [d]);
    },
    b = function (b) {
      if (b.length) {
        var c = parseInt(b[0]),
          b = parseInt(b[1]),
          e = 0 == b ? 0 : Math.round(100 * (c / b)),
          f = $rs.findIn(a, ".rsbtn_current_time"),
          k = $rs.findIn(a, ".rsbtn_total_time"),
          m,
          j;
        q || (d.progress.jumpTo(e), i(e), f && (f.innerHTML = m = l(c)), k && (k.innerHTML = j = l(b)), rspkr.cfg.execCallback("cb.ui.timeupdated", a, [m, j]));
        d.progress.setAttr("current", c);
        d.progress.setAttr("buffered", b);
        rspkr.log("[rspkr.player.updateProgress] current time: " + c + " total time: " + b);
        0 < c && $rs.removeClass($rs.findIn(a, ".rsbtn_progress_container"), "rsloading");
      }
    },
    l = function (a) {
      var a = a / 1e3,
        d = parseInt(a % 60),
        b = parseInt((a / 60) % 60),
        a = parseInt((a / 60 / 60) % 60);
      return (10 > a ? "0" + a : a.toString()) + ":" + (10 > b ? "0" + b : b.toString()) + ":" + (10 > d ? "0" + d : d.toString());
    },
    n = function () {
      q = !0;
    },
    p = function (a) {
      a = ((a / 100) * d.progress.getAttr("buffered")) / 1e3;
      rspkr.pl.setProgress(a);
      q = !1;
    },
    t = function (a) {
      p(a);
    },
    u = function (b) {
      b = 0 > b ? 0 : 20 * b;
      d.vol && d.vol.jumpTo(b / 20);
      rspkr.pl.setVolume(b);
      rspkr.st.set("hlvol", b);
      rspkr.cfg.execCallback("cb.ui.volumechanged", a, [b]);
      return !1;
    },
    v = function (a, b) {
      rspkr.log("[rspkr.ui.Player] focusIn(" + a.className + ", " + b.className + ")", 5);
      if ("keyLink" === a.className) {
        var c = "";
        $rs.hasClass(b, "volume_handle") ? (c = "vol") : $rs.hasClass(b, "progress_handle") && (c = "progress");
        d[c].startDragKeys(a, { keyCode: 13 });
      }
    },
    w = function (a, b) {
      rspkr.log("[rspkr.ui.Player] focusOut(" + a.className + ")", 5);
      if ("keyLink" === a.className) {
        var c = "";
        $rs.hasClass(b, "volume_handle") ? (c = "vol") : $rs.hasClass(b, "progress_handle") && (c = "progress");
        d[c].releaseElement();
        q = !1;
      }
    };
  return {
    init: function () {
      r.push([this.show, []]);
    },
    show: function () {
      $rs.rsid(a);
      a.id = c = a.id || rspkr.getID();
      ui = rspkr.ui;
      $rs.hasClass(a, rspkr.ui.rsbtnClass) || $rs.addClass(a, rspkr.ui.rsbtnClass);
      if (0 == $rs.findIn(a, ".rsbtn_exp").length) {
        var b = null,
          h = rspkr.cfg,
          i = $rs.hasClass(a, "rspopup") ? h.item("ui.popupplayer") : h.item("ui.player"),
          h = rspkr.cfg.getPhrases(rspkr.c.data.getParam("lang")),
          b = document.createElement("span");
        b.className = "rsbtn_exp rsimg rspart";
        b.innerHTML += i.join("\n");
        a.appendChild(b);
        "fallback" === rspkr.pl.adapter && rspkr.ui.showOverlay("nosound", a);
        if (h) {
          e.pause() && ($rs.setAttr(e.pause(), "data-rsphrase-pause", h.pause), $rs.setAttr(e.pause(), "data-rsphrase-play", h.play), $rs.setAttr(e.pause(), "title", rspkr.c.decodeEntities(h.pause)));
          e.stop() && $rs.setAttr(e.stop(), "title", rspkr.c.decodeEntities(h.stop));
          e.vol() && $rs.setAttr(e.vol(), "title", rspkr.c.decodeEntities(h.volume));
          e.settings() && $rs.setAttr(e.settings(), "title", rspkr.c.decodeEntities(h.settings));
          e.dl() && $rs.setAttr(e.dl(), "title", rspkr.c.decodeEntities(h.download));
          if (e.powered()) {
            var b = $rs.findIn(e.powered(), ".rsbtn_btnlabel"),
              i = h.speechenabled.match(/.*href="([^"]*)"/i).pop(),
              l = document.createElement("p");
            l.innerHTML = h.speechenabled;
            l = l.innerText || l.textContent;
            b && (b.innerHTML = h.speechenabled);
            $rs.setAttr(e.powered(), "title", l);
            $rs.setAttr(e.powered(), "data-readspeaker-href", i);
            $rs.regEvent(e.powered(), "click", function () {
              window.open($rs.getAttr(this, "data-readspeaker-href"));
            });
          }
          e.closer() && $rs.setAttr(e.closer(), "title", rspkr.c.decodeEntities(h.closeplayer));
        }
        h = rspkr.c.data.browser;
        (!/safari/i.test(h.name) || !/iphone|ipad|ios/i.test(h.OS)) && $rs.addClass(a, "rs-no-touch");
      }
      $rs.addClass(a, "rsexpanded");
      if (rspkr.basicMode) {
        var j;
        (j = $rs.findIn(a, ".rsbtn_play")) && $rs.addClass(j, "rsexpanded");
      }
      if (!k) {
        e.stop() &&
          ($rs.regEvent(e.stop(), "click", function () {
            f.stop();
          }),
            ui.addFocusHandler(e.stop()));
        e.pause() &&
          ($rs.regEvent(e.pause(), "click", function () {
            $rs.hasClass(a, "rsplaying") ? f.pause() : ($rs.hasClass(a, "rsstopped") || $rs.hasClass(a, "rspaused")) && f.play();
          }),
            ui.addFocusHandler(e.pause()));
        e.closer() &&
          ($rs.regEvent(e.closer(), "click", function () {
            f.close();
          }),
            ui.addFocusHandler(e.closer()));
        e.vol() &&
          ($rs.regEvent(e.vol(), "click", function (a) {
            f.vol(a);
          }),
            ui.addFocusHandler(e.vol()));
        e.dl() &&
          ($rs.regEvent(e.dl(), "click", function () {
            return f.dl();
          }),
            ui.addFocusHandler(e.dl()));
        e.settings() &&
          ($rs.regEvent(e.settings(), "click", function () {
            f.settings();
          }),
            ui.addFocusHandler(e.settings()));
        if ($rs.findIn(a, ".rsbtn_powered") && (j = $rs.findIn(a, ".rsbtn_powered .rsbtn_btnlabel a")))
          j.innerHTML = '<span class="rsbtn_label_read">Read</span><span class="rsbtn_label_speaker">Speaker</span><span class="rsbtn_label_icon rsimg"></span>';
        j = rspkr.cfg;
        $rs.isArray($rs.findIn($rs.get(a), ".rsbtn_progress_container")) ||
          ((d.progress = new rspkr.ui.Slider()),
            d.progress.init($rs.findIn($rs.get(a), ".rsbtn_progress_container"), {
              handleClass: j.item("ui.progressHandleClass") || "rsbtn_progress_handle rsimg",
              dir: j.item("ui.progressDir") || "h",
              start: n,
              drop: p,
              click: t,
              labelDragHandle: j.getPhrase("sliderseek"),
            }),
            d.progress.setAttr("current", 0),
            d.progress.setAttr("buffered", 0),
            (h = $rs.findIn($rs.get(a), ".rsbtn_progress_handle a")),
            ui.addFocusHandler(h, !1, h.parentNode));
        $rs.isArray($rs.findIn($rs.get(a), ".rsbtn_volume_slider")) ||
          ((h = rspkr.st.get("hlvol") || "100"),
            (h = 5 * (parseInt(h) / 100)),
            (d.vol = new rspkr.ui.Slider()),
            d.vol.init($rs.findIn(a, ".rsbtn_volume_slider"), {
              handleClass: j.item("ui.volumeHandleClass") || "rsbtn_volume_handle rsimg",
              dir: j.item("ui.volumeDir") || "v",
              steps: 5,
              initval: h,
              drop: u,
              click: u,
              labelDragHandle: j.getPhrase("slidervolumedesc"),
            }),
            (h = $rs.findIn($rs.get(a), ".rsbtn_volume_handle a")),
            ui.addFocusHandler(h, !1, h.parentNode));
        rspkr.Common.addEvent("onFocusIn", v);
        rspkr.Common.addEvent("onFocusOut", w);
        rspkr.cfg.execCallback("cb.ui.open", a);
        k = !0;
      }
      d.progress && "0" != d.progress.getAttr("current") && (rspkr.pl.releaseAdapter(), d.progress.setAttr("current", 0));
      "fallback" !== rspkr.pl.adapter && (f.play(), rspkr.ui.focus(e.pause()));
      j = (j = a) || a;
      j = $rs.clone(j, !0, !0);
      j.id = rspkr.getID();
      document.body.appendChild(j);
      $rs.css(j, { position: "absolute", top: "0", left: "0", display: "block", width: "auto" });
      $rs.css(j, "float", "none");
      $rs.addClass(j, "rsexpanded");
      h = $rs.outerWidth(j) + 3;
      j.style.display = "none";
      document.body.removeChild(j);
      m = h;
      isNaN(m) || $rs.css(a, "width", m + (/[Ee]xplorer/.test(ReadSpeaker.c.data.browser.name) ? 1 : 0) + "px");
    },
    close: function (a) {
      f.close(a);
    },
    stop: function () {
      f.stop();
    },
    nosound: function () {
      return f.nosound();
    },
    restart: function () {
      rspkr.log("[rspkr.ui.restart]");
      f.stop();
      window.setTimeout(function () {
        f.play();
      }, 500);
      return !1;
    },
    updateProgress: function (a) {
      b(a);
    },
    setProgress: function (a) {
      p(a);
    },
    getContainer: function () {
      return a;
    },
    getID: function () {
      return c;
    },
    getWidth: function () {
      return m;
    },
    setHref: function (a) {
      s = a;
    },
    getHref: function () {
      return s;
    },
  };
};
ReadSpeaker.ui.Lightbox = (function () {
  var a = null,
    c = null,
    j = null,
    r = null,
    m = null,
    k = null,
    s,
    e = function () {
      $rs.css(k, "display", "none");
      var a = $rs.height(window),
        c = $rs.height(document),
        e = parseInt($rs.css(document.documentElement, "width")),
        b = $rs.width(document),
        j = $rs.absOffset(document.body),
        n = 0,
        p = 0;
      isNaN(e) && (e = $rs.width(window));
      j.left && (p = j.left);
      j.top && (n = j.top);
      $rs.css(m, { width: (b > e ? b : e) + "px", height: (c > a ? c : a) + "px", top: "-" + Math.abs(n) + "px", left: "-" + Math.abs(p) + "px" });
      $rs.css(k, "display", "block");
      a = $rs.outerWidth(k);
      c = $rs.outerHeight(k);
      e = $rs.width(window);
      b = $rs.height(window);
      c = s + 80 + 50 < b ? s + 80 : b - 50;
      k.style.height = c + "px";
      $rs.get("#rslightbox_content").style.height = c - 80 + "px";
      c > b ? ((k.style.top = $rs.scrollTop(document) + "px"), (k.style.marginTop = "10px")) : ((k.style.top = b / 2 + "px"), (k.style.marginTop = -(c / 2 - $rs.scrollTop(document)) + "px"));
      a > e ? ((k.style.left = $rs.scrollLeft(document) + "px"), (k.style.marginLeft = "0")) : ((k.style.left = "50%"), (k.style.marginLeft = -(a / 2 - $rs.scrollLeft(document)) + "px"));
    },
    q = function (a) {
      27 === a.keyCode && rspkr.ui.Lightbox.hide();
    };
  return {
    init: function () {
      var d = rspkr.pub.Config;
      a = d.item("ui.overlay.overlayStyles");
      c = d.item("ui.overlay.contentStyles");
      j = d.item("ui.overlay.contentTemplate");
      rspkr.log("[rspkr.ui.Lightbox] Heartbeat!");
    },
    show: function (d, f, i, b) {
      d = d || "";
      i = i || !1;
      m
        ? ((m.style.display = ""), (k.style.display = ""))
        : ((m = document.createElement("div")),
          (m.id = "rslightbox_overlay"),
          (k = document.createElement("div")),
          (k.id = "rslightbox_contentcontainer"),
          (k.innerHTML = rspkr.st.r().replaceTokens(j.join("\n"), { rsLIGHTBOX_CLOSE_LABELrs: rspkr.cfg.getPhrase("close") })),
          $rs.setAttr(m, "style", a.join(";")),
          $rs.setAttr(k, "style", c.join(";")),
          document.body.appendChild(m),
          document.body.appendChild(k),
          rspkr.evt("onSettingsLoaded", { func: rspkr.st.r().handlers.changed.addButtonEvents, context: rspkr.st.r().handlers.changed, params: [this] }));
      var l = $rs.get("rslightbox_closer");
      rspkr.ui.addFocusHandler(l, !1);
      $rs.regEvent(l, "click", rspkr.ui.Lightbox.hide);
      $rs.regEvent(m, "click", rspkr.ui.Lightbox.hide);
      $rs.regEvent(document.body, "keyup", q);
      if ((l = document.documentElement) && document.all) l.style.overflowX = l.style.overflowY = "hidden";
      if (d != r || i)
        ($rs.get("#rslightbox_content").innerHTML = ""),
          $rs.css("#rslightbox_content", "height", "auto"),
          /^http/i.test(d)
            ? $rs.findIn("#rslightbox_content", "iframe").length || ((i = document.createElement("iframe")), (i.src = d), (i.className = "rslightbox-iframe"), $rs.get("#rslightbox_content").appendChild(i))
            : "<" == d.substr(0, 1) && ($rs.get("#rslightbox_content").innerHTML = d),
          ($rs.get("#rslightbox_buttons").innerHTML = f),
          (r = d);
      s = !rspkr.basicMode ? $rs.get("#rslightbox_content").clientHeight : $rs.get("#rslightbox_content").scrollHeight;
      d = $rs.findIn("#rslightbox_content", ".rsform-row");
      for (i = 0; i < d.length; i++) {
        f = $rs.findIn(d[i], "input, a, select");
        $rs.isArray(f) || (f = [f]);
        for (l = 0; l < f.length; l++) rspkr.ui.addFocusHandler(f[l], !1, d[i]);
      }
      var n = $rs.findIn("#rslightbox_buttons", ".rssettings-button-close");
      rspkr.ui.addFocusHandler(n, !1);
      (d = $rs.findIn("#rsform_wrapper", ".rssettings-button-gotobottom")) && !$rs.isArray(d) && rspkr.ui.addFocusHandler(d, !1);
      (d = $rs.findIn("#rslightbox_buttons", ".rssettings-button-gototop")) && !$rs.isArray(d) && rspkr.ui.addFocusHandler(d, !1);
      var p = $rs.findIn("#rslightbox_content", "input");
      $rs.isArray(p) && 0 < p.length
        ? setTimeout(function () {
          rspkr.ui.focus(p[0]);
          rspkr.Common.addEvent("onFocusIn", function (a) {
            a.className && $rs.hasClass(a, "rssettings-button-gototop") ? rspkr.ui.focus(p[0]) : a.className && $rs.hasClass(a, "rssettings-button-gotobottom") && rspkr.ui.focus(n);
          });
        }, 200)
        : $rs.isArray(p) ||
        setTimeout(function () {
          rspkr.ui.focus(p);
        }, 200);
      e();
      $rs.regEvent(window, "resize", e);
      "function" == typeof b && b.apply(this, [k]);
    },
    hide: function () {
      m.style.display = "none";
      k.style.display = "none";
      $rs.unregEvent(window, "resize", e);
      $rs.unregEvent($rs.get("#rslightbox_closer"), "click", rspkr.ui.Lightbox.hide);
      $rs.unregEvent(m, "click", rspkr.ui.Lightbox.hide);
      $rs.unregEvent(document.body, "keyup", q);
      var a;
      if ((a = document.documentElement) && document.all) a.style.overflowX = a.style.overflowY = "auto";
      rspkr.ui.updateFocus();
    },
  };
})();
