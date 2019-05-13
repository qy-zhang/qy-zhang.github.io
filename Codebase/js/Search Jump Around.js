// ==UserScript==
// @name           Search Jump Around
// @namespace      http://userscripts.org/users/86496
// @description    Jump between web searches of Google, Baidu, Youdao, Bing and more.
// @version        2.22

// @include        https://www.google.com/*
// @include        https://www.google.com.hk/search?q=*
// @include        https://www.google.co.jp/*
// @include        https://encrypted.google.com/*
// @include        http://*.bing.com/*
// @include        https://*.bing.com/*
// @include        https://www.baidu.com/s*


// ==/UserScript==

// Special credit for Dave Child
// Mod by hzhbest
// Version 1.12 20100125
// Version 2.00 20100802

// Customization
// ---------------------------------
// openNewWin - 是否在新窗口（标签）显示跳转的搜索页面（1－是；0－否） |Show jumped page on new window / tab (1-yes; 0-no)
// engArr[i].on - 搜索引擎开关，“1”为“启用”|Whether to show this engine in list or not
// engArr[i].type - 搜索引擎类型|Search engine type
//			0 - 综合类|General
//			1 - 图片类|Image
//			2 - 视频类|Video
//			3 - 新闻类|News
//			4 - 购物类|Shop
//			5 - 博客类|Blog
//			6 - 地图类|Map
//			7 - 音乐类|Music
//			-1 - 任何情况下都显示|Override
// engArr[i].icon - 搜索引擎网站图标|Search engine favicon
// engArr[i].name - 搜索引擎名称|Search engine name
// engArr[i].kwI - 识别URL中搜索关键词的关键字|Querystring variable key for keywords entered
// engArr[i].url1 - 识别搜索网站的URL关键字1|URL portion identifying search from this engine
// engArr[i].url2 - 识别搜索网站的URL关键字2|URL portion identifying search from this engine
// engArr[i].urlS - 搜索引擎URL（“--keywords--”用于替换搜索关键词）|Search URL ("--keywords--" to be replaced by searched-for keywords)
//			--keywords-- - 替换UTF-8编码关键词
//			(-=keywords=- - 替换GB2312编码关键词;暂时无效)
// icons - 搜索引擎网站图标URL|Search engine favicon



(function() { //var l = console.log;

var engArr = [];
var lg = [];
var favImg = [];
var titlebox, config_btn;
var CO = 'SearchJumpAround_config';

if (typeof GM_getValue == "function") {
	var get_config = GM_getValue;
	var set_config = GM_setValue;
} else { // workaround functions, creadit to ww_start_t
	var set_config = function(cookieName, cookieValue, lifeTime){
		if (!cookieName) {return;}
		if (lifeTime == "delete") {lifeTime = -10;} else {lifeTime = 31536000;}
		document.cookie = escape(cookieName)+ "=" + escape(getRecoverableString(cookieValue))+
			";expires=" + (new Date((new Date()).getTime() + (1000 * lifeTime))).toGMTString() + ";path=/";
	};
	var get_config = function(cookieName, oDefault){
		var cookieJar = document.cookie.split("; ");
		for (var x = 0; x < cookieJar.length; x++ ) {
			var oneCookie = cookieJar[x].split("=");
			if (oneCookie[0] == escape(cookieName)) {
				try {
					eval('var footm = '+unescape(oneCookie[1]));
				} catch (e) {return oDefault;}
				return footm;
			}
		}
		return oDefault;
	};
}

var config = get_config(CO, '1|0|120').split('|');
for (i in config) {config[i] = Number(config[i]);}
var nw = config[0]; // Open in new window/tab, "0" false, "1" true.
var lt = config[0]; // Show SJA bar on left, "0" false, "1" true.
var tp = config[2]; // SJA bar's top position, pixel.
//l(nw,lt,tp);
// ## Customization | 自定义区 ##

	var icons = {
		google : "data:image/x-icon;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAQAQAABILAAASCwAAAAAAAAAAAAD0hUJK9IVC5/SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQuT0hUJK9IVC5vSFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC5/SFQv/0hUL/9IVC//SFQv/1jU7/+sir//7v5//95df/+9S9//vPtf/3oW7/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/+9jC//3s4f/1lFn/9IVC//SFQv/0iEb//NvH//eibv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//3u5f/5u5b/9IVC//SFQv/0hUL/9IVC//m6lP/707r/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/5vpv//N7M//SIR//0hUL/9IVC//WSV//97OH/+8+0//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//epev/6yKr/+byW//nCoP/+9O7//e3j//WSVv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SHRv/+9vH//OLT//WPUf/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//aeaf/5uZL////+//iwhf/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//m4kf//+/n/96h5//WNT//7zbL/9p9q//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/+9fD/+86z//SFQv/0hUL/96Rx//3r4P/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL//vby//iwhf/0hUL/9IVC//izif//+/j/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//rIqf/5vJf/9IVC//SGRP/95NX/+9a///SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hkT/+bqU//m7lv/84dD///79//rLr//3p3f/9IVC//SFQv/0hUL/9IVC//SFQub0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQub0hUJJ9IVC5vSFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQv/0hUL/9IVC//SFQub0hUJJAAA3MAAAUHIAAHJhAABhdAAAQzoAAHJvAABhbQAAdGEAAHJvAABhbQAAbGUAAEM6AABybwAAYW0AAGlsAAAAUA=="
			// 'https://www.google.com/favicon.ico'
		,wikipedia : "data:image/x-icon;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAQAQAABMLAAATCwAAAAAAAAAAAAD///8F////Yf///8v/////////////////////////////////////////////////////////y////2H///8F////Yf//////////////////////////////////////////////////////////////////////////////Yf///8v/////////////////////2NjY//39/f////////////T09P/k5OT//////////////////////////8v/////////////////////+vr6/xsbG/+QkJD///////////9tbW3/Pj4+/////////////////////////////////////////////////6CgoP8KCgr/RkZG//j4+P/t7e3/CgoK/zk5Of/MzMz///////////////////////////////////////////8sLCz/a2tr/7Ozs/+Tk5P/g4OD/ycnJ//q6ur/ZGRk//////////////////////////////////////+3t7f/AgIC/93d3f//////TU1N/xUVFf+hoaH//////2ZmZv/l5eX/////////////////////////////////QkJC/1RUVP///////////2tra/8UFBT/+/v7///////MzMz/eXl5////////////////////////////zc3N/wAAAP/IyMj///////v7+/8jIyP/Ly8v//f39////////////0pKSv/19fX//////////////////////1lZWf89PT3///////////+ampr/HR0d/62trf+Kior///////////+kpKT/lpaW/////////////////+Dg4P8EBAT/sbGx///////19fX/ICAg/5OTk///////QkJC/+7u7v//////+fn5/zs7O//7+/v//////8/Pz/9AQED/AAAA/5SUlP/9/f3/R0dH/wAAAP+enp7/4uLi/zo6Ov9DQ0P/5eXl/6+vr/8TExP/UFBQ/9fX1//8/Pz/9/f3//f39//4+Pj///////f39//39/f/+vr6//39/f/39/f/9/f3//39/f/6+vr/9/f3//f39//8/Pz/////y///////////////////////////////////////////////////////////////////////////////y////2H//////////////////////////////////////////////////////////////////////////////2H///8F////Yf///8v/////////////////////////////////////////////////////////y////2H///8FwAM3MIABUHIAAHJhAABhdAAAQzoAAHJvAABhbQAAdGEAAHJvAABhbQAAbGUAAEM6AABybwAAYW2AAWlswAMAUA=="
			//'https://zh.wikipedia.org/favicon.ico'
		,youtube : "data:image/x-icon;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAQAQAABMLAAATCwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgNkQkIDZGiCA2RzAgNkcwIDZH/CA2R/wgNkf8IDZH/CA2R/wgNkf8IDZH/CA2R2AgNkcwIDZHMCA2RhAgNkQYIDpWHCA6V/wgOlf8IDpX/CA6V/wgOlf8IDpX/CA6V/wgOlf8IDpX/CA6V/wgOlf8IDpX/CA6V/wgOlf8IDpWHCQ6ZzAkOmf8JDpn/CQ6Z/wkOmf8JDpb/BQhc/wgMgf8JDpn/CQ6Z/wkOmf8JDpn/CQ6Z/wkOmf8JDpn/CQ6ZzAkOnuoJDp7/CQ6e/wkOnv8JDp7/Exed/8jIy/9RU4j/Bwp0/wkOm/8JDp7/CQ6e/wkOnv8JDp7/CQ6e/wkOnuoJD6T8CQ+k/wkPpP8JD6T/CQ+k/xUbo//V1dX/1dXV/4yNrP8QFG//CA6Y/wkPpP8JD6T/CQ+k/wkPpP8JD6T8CQ+q/wkPqv8JD6r/CQ+q/wkPqv8WG6n/3d3d/93d3f/d3d3/v7/M/y0wjv8JD6r/CQ+q/wkPqv8JD6r/CQ+q/woQr/8KEK//ChCv/woQr/8KEK//Fx2v/+fn5//n5+f/5+fn/+jo6P+YmtP/ChCv/woQr/8KEK//ChCv/woQr/8KELX8ChC1/woQtf8KELX/ChC1/xgdtf/x8fH/8fHx//Ly8v+bndv/Ehi3/woQtf8KELX/ChC1/woQtf8KELX8ChG76goRu/8KEbv/ChG7/woRu/8YH77/+fn5/+/v9/9fY9H/ChG7/woRu/8KEbv/ChG7/woRu/8KEbv/ChG76goRwMwKEcD/ChHA/woRwP8KEcD/EBfB/6Ol5/8tM8n/ChHA/woRwP8KEcD/ChHA/woRwP8KEcD/ChHA/woRwMwLEcSHCxHE/wsRxP8LEcT/CxHE/wsRxP8LEcT/CxHE/wsRxP8LEcT/CxHE/wsRxP8LEcT/CxHE/wsRxP8LEcSHCxLICQsSyKULEsjMCxLI+QsSyP8LEsj/CxLI/wsSyP8LEsj/CxLI/wsSyP8LEsj/CxLI0gsSyMwLEsiiAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA//8AAP//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABAAD//wAA//8AAA=="
			//'https://www.youtube.com/favicon.ico'	
		,googletrans : "data:image/x-icon;base64,AAABAAEAEBAAAAEACABoBQAAFgAAACgAAAAQAAAAIAAAAAEACAAAAAAAQAEAABMLAAATCwAAAAEAAAAAAAAAAAAA1pYeAK+6ugDkmgkA0Y0HAP+2MADO3d4A0qRFAHN8eQDr9PYAz7h/AMrUzwDV5ecA/8JXALFYAQDtzYoA3+vtAOTcvQD/ynAAwcrHAMNkAgDccwQA2ObpAJSdmwBaYl4A+qkSAImBaQDgoSoA1OLkAN+bHwD1u0wAz8qtAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAOABsdHR0dAQEBAAAAFBQUDg4EBAMDAwQEBAQAFBQUDg4ODgYHAwMDExMEABQVFBQODh4GHwcHCgsKBAAVFRUADhkZCxwGBgYLGwQVFRUVFQwFBQ8cCh4GHwMDFhUVFRwcBQUeDB8PBh4DAxYLFRMCCw0eHhEWCwYZGQMQEAYIGBgNDQ0PFgwPGRkDEBAQAhgYEhISDRERHhkZGRAQEBgIFw8SEhINHgUZGRkJCRMYCxwaEhISDR4FGRkACRcIGAgIGBgIHAAAAAAAAAkXCAgYGAgICBwAAAAAAAAJCQkJAhcQEBYMAAAAAAAAAAkJCQkQEBAWAAAAAAAAAPoBAADAAAAAgAAAAIAAAACIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEAAAA/AAAAPwAAAD8AAIB/AAA="
		,tpb : "data:image/ico;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAQAQAAOVMAADlTAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAC9vb027OzsBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA4uLiCklJSf/d3d0NAAAAAAAAAADz8/MBEhIS/3Jyctfx8fECAAAAAAAAAAAAAAAAAAAAAAAAAADx8fECwsLCLVhYWPcAAAD/yMjIJAAAAAAAAAAA5+fnBhAQEP8gICD/QkJC/1dXV/hlZWXqi4uLpomJiatSUlL7Kioq/z09Pf9ubm7fHh4e/2FhYe/BwcEvubm5O2xsbOJAQED/p6enYHd3d88UFBT/AAAA/xQUFP85OTn/ISEh/xkZGf89PT3/WVlZ90JCQv8qKir/Jycn/3p6esoAAAD/QUFB/z8/P/9gYGDwjo6OodHR0RkAAAAAAAAAAAAAAADv7+8CxcXFKJ2dnXmDg4O4ExMT/0BAQP+/v78yAAAA/4KCgrqOjo6hpaWlZLa2tkGqqqpYpqamYqWlpWSkpKRnra2tVK+vr0+xsbFL5eXlB5eXl4tbW1v01NTUFXFxcdqYmJiIAwMD/wAAAP83Nzf/VFRU+hsbG/8AAAD/X19f8Tw8PP8RERH/AAAA/0FBQf8AAAAAAAAAAAAAAAAAAAAAnJycfAAAAP8AAAD/AAAA/x8fH/8LCwv/AAAA/yYmJv8FBQX/AAAA/wAAAP8rKyv/AAAAAAAAAAAAAAAAAAAAAJycnHwAAAD/AAAA/w8PD/8AAAD/AAAA/wAAAP8AAAD/DQ0N/wMDA/8AAAD/NjY2/wAAAAAAAAAAAAAAAAAAAACurq5SAAAA/zY2Nv/l5eUHWVlZ9x8fH/8nJyf/IyMj/9HR0RmGhoayAAAA/1dXV/gAAAAAAAAAAAAAAAAAAAAAr6+vTwAAAP8tLS3/0tLSGF9fX/GysrJJ2dnZEWVlZeqysrJJiIiIrQAAAP9ZWVn3AAAAAAAAAAAAAAAAAAAAAK+vr08AAAD/AAAA/wUFBf8CAgL/ExMT/xAQEP8DAwP/AwMD/wEBAf8AAAD/Wlpa9QAAAAAAAAAAAAAAAAAAAACrq6tYAAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP8AAAD/AAAA/1RUVPoAAAAAAAAAAAAAAAAAAAAA19fXE0lJSf9BQUH/Q0ND/0NDQ/9DQ0P/Q0ND/0NDQ/9DQ0P/QkJC/0JCQv+oqKhdAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA//8gIM/xICCHwSAggAAgIAAAICABwCAgAAAgIAADICDAAyAgwAMgIMADICDAAyAgwAMgIMADICDAAyAg//8gIA=="
		,bts : "data:image/ico;base64,AAABAAEAEBAAAAAAAABoBQAAFgAAACgAAAAQAAAAIAAAAAEACAAAAAAAAAEAAAAAAAAAAAAAAAEAAAAAAAAAAAAAN5SQADG6tQA0pKAAM6ikADt4dgAuy8UAMrWwADWgmwA8c3EAO3d1ADKvqwAwwLoAM6qlAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGBgYGBgYGBgYGBgYAAAAGBgYGBgYGBgYGBgYGBgAGBgYGBgYGBgYGBgYGBgYGBgYGBgwBCQkJCQEMBgYGBgYGBgwFCQkJCQkJBQwGBgYGBgYBCQkFDQgKCQkBBgYGBgYGCQkJAwIJCQkJCQYGBgYGBgkJCQcCCQkJCQkGBgYGBgYJCQkHBgIECQkJBgYGBgYGCQkJAwYGAwkJCQYGBgYGBgEJCQULCwUJCQEGBgYGBgYMBQkJCQkJCQUMBgYGBgYGBgwBCQkJCQEMBgYGBgYGBgYGBgYGBgYGBgYGBgYABgYGBgYGBgYGBgYGBgYAAAAGBgYGBgYGBgYGBgYAAMADAACAAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgAEAAMADAAA="
		,twitter :"data:image/ico;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAQAQAABMLAAATCwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD268848NyoZ+3PiIjtz4mJ8dqiafXqyzkAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAPTnyEvluVbL3JcA/9qLAP/gmAD/4J0M/9+aB//fnhD/5LA74fHapmoAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD49OQi+vPfIffw2TLv2qVt5bJE3uOlIP/kqi7/5Kot/+KhFf/elQD/5bhUyfz9+wsAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA9u7XOOO3UMvgoxz/5Kos/+SqLf/kqy7/5asv/92WAP/js0Xe/f7/BAAAAAAAAAAAAAAAAAAAAAD8/fsF6MRvtN2UAP/iohn/5Kwy/+SqLf/kqi3/5Kot/+SqLf/lqzD/3pUA/+jFcrcAAAAAAAAAAAAAAAAAAAAAAAAAAOW+YM/gohv+5Kkr/+SqLf/kqi3/5Kot/+SqLf/kqi3/5Kou/+SoKP/emgf/9OfERwAAAAAAAAAAAAAAAPLkvlrkrjfZ4aYl/uSpLP/kqi3/5Kot/+SqLf/kqi3/5Kot/+SqLf/kqy//4JkE/+nBaL4AAAAAAAAAAPjw2S7dmQT/4aAT/+WsMf/kqi3/5Kot/+SqLf/kqi3/5Kot/+SqLf/kqi3/5Kot/+OjHv/jrDH9+fnwEAAAAAD05L1T5LVLzeKpK/rkqSv/5aot/+OkH//gnQz/4J4Q/+SrMP/kqi7/5Kot/+SqLf/kqCn/4aAV//Tox0YAAAAAAAAAAOjFcb3hoRb+4p8S/96dDP/ksDzp7ch2qevJearjpyb/5Kkr/+SqLf/kqi3/5Kkq/+CdDP/26cxCAAAAAPPjvVHfmQP/3pgB/+S0R9fz47pRAAAAAAAAAAD58+Ej4JwO/+SoKv/kqi3/5Kot/+SqLP/hoRb/6b9iuPj58BPv15t82okA/+nOhpEAAAAAAAAAAAAAAAAAAAAA+fnuEuGpK//hnQ3/5awx/+WrMP/kqCj/3ZcA/+CmI//y475W9efCSuvTloYAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADx5cBT3Z4O/92XAP/dlwD/3qQe/+nFcZ/oxXC58+fKSQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAPjy4yzszISF6sx+iPbs1TUAAAAAAAAAAPTx3isAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA//8gIMD/ICAAPyAgAA8gIOAHICCAByAgwAMgIIADICAAASAgAAEgIIABICAGACAgHgAgID8AICD/hiAg//8gIA=="
		,wolfa :"data:image/ico;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAdNOsAHTTrAB006wAdNOsAHTTrAB00628dNOtPHTTrAR006wAdNOsAHTTrBR006wcdNOsAHTTrAB006wD///8AHTTrAB006wAdNOsAHTTrAB006wAdNOumHTTrzh006wUdNOsAHTTrEh00630dNOs7HTTrAB006wAdNOsA////AB006wAdNOsFHTTrJB006wodNOsAHTTrqh006/8dNOthHTTrLx0065MdNOvQHTTrCR006wAdNOsAHTTrBv///wAdNOsAHTTrCR0063kdNOurHTTrYB0068odNOv/HTTr/x006+cdNOv/HTTrqB006wAdNOstHTTrgR006yr///8AHTTrAB006wAdNOsiHTTr1x416/8WLur/Eyvq/xUt6v8ULOr/FS3q/x416+UdNOuTHTTr4x0067QdNOsY////AB006wAdNOsAHTTrCR0067MVLer/FS3q/xUt6v8VLer/FS3q/xUt6v8VLer/HjXr/x0067AdNOsNHTTrAP///wAdNOuuHTTrzh0069QaMev3FS3q/+/x/v/v8f7/7/H+/+/x/v/v8f7/FS3q/xYt6v8dNOtTHTTrAB006wD///8AHTTrVB00680dNOv/HDPr/xUt6v8VLer/FS3q/xUt6v8VLer/FS3q/xUt6v8cM+v/HTTrwB006yMdNOsE////AB006wAdNOsFHTTrbxwz6/8VLer/FS3q/xUt6v8VLer/FS3q/xUt6v8VLer/HDPr/x006/0dNOvtHTTrpv///wAdNOsAHTTrAB0062UWLur/FS3q/+/x/v/v8f7/7/H+/+/x/v/v8f7/FS3q/xYu6uwdNOuRHTTrUB0061n///8AHTTrAh00600dNOvxHjXr/xUt6v8VLer/FS3q/xUt6v8VLer/FS3q/xUt6v8eNeu/HTTrDB006wAdNOsA////AB006w0dNOuKHTTrix0063UeNevZFi7q/xQs6v8VLer/FCzq/xUt6v8eNev/HTTr/x0062gdNOsAHTTrAP///wAdNOsHHTTrFB006wAdNOsAHTTrsR006/8dNOuiHTTr/x006/4dNOurHTTrWx0066EdNOvEHTTrIB006wD///8AHTTrAB006wAdNOsAHTTrUx006/kdNOtwHTTrCB0061IdNOv3HTTrTh006wAdNOsHHTTrSB006xcdNOsA////AB006wAdNOsAHTTrAB0062odNOtwHTTrAB006wAdNOsAHTTrwh0062EdNOsAHTTrAB006wAdNOsAHTTrAP///wAdNOsAHTTrAB006wIdNOsNHTTrAR006wAdNOsAHTTrAR006zsdNOtCHTTrAB006wAdNOsAHTTrAB006wD///8A//8AAPn/AAD5nwAA6BsAAOADAADgBwAAAA8AAIAHAADgAQAA4AcAAMAPAACQDwAA8CcAAPd/AAD/fwAA//8AAA=="
		,amazon : "data:image/ico;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAQAQAABMLAAATCwAAAAAAAAAAAAAAAAAA////jP///+L////w////8P////DX7//wt+X/8MDn//Do9//w////8P////D////w////4f///4kAAAAA////kf//////////5fb//1rD//8Kpf//AJ7//wCf//8An///AKH//yqw//+U1///////////////////////i/////f/////iNX//xqq//8ssv//fdD//7Pm///P7v//y+3//6fg//9oxv//Lq///3nQ//+i3v//0+////////T9/v/2mtv//0/B///E6f////////////////////////////////////////////9qyf//HKr//4LU///////2/P7/8Nfx/////////////+De3P9ycnL/V1dX/4ODg//6+vr//////4mJiP/w8O//2vn//5nU///Q7v//////8P////D//////////9/f3/8MDAz/AAAA/wAAAP8AAAD/IiIh/1VVVP8AAAD/JiQi//Hh2P////////////////D////w//////////9/f3//AAAA/wAAAP9cXFv/q6ur/wwMC/8AAAD/AAAA/wAAAP/S0tL////////////////w////8P//////////bGxr/wAAAP8AAAD/5+fn//////+2trb/AAAA/wAAAP9vb27/////////////////////8P////D//////////6ysq/8AAAD/AAAA/4ODg////////////wQEBP8AAAD/fHx6//////////////////////D////w////////////////WVlY/wAAAP8AAAD/JiYl/1ZWVf8MDAv/AAAA/3R0c//////////////////////w////8P/////////////////////S0tL/ZGRj/x0dHf8AAAD/BQUE/wAAAP9ycnH/////////////////////8P////D//////////+fn5/+kpKT/rq6t////////////8vLx/wQEBP8AAAD/c3Nz//////////////////////D////2///////////S0tH/AAAA/wAAAP9mZmX/6+vr/5qamf8AAAD/AAAA/4WFhP/////////////////////2////+P///////////////2dnZv8AAAD/AAAA/wAAAP8AAAD/AAAA/wAAAP/W1tb/////////////////////9P///5P/////////////////////jY2N/zs7Ov8CAgH/EhIR/1BQT//FxcX//////////////////////////40AAAAA////jv///+T////w////8P////D////w8PDw8PX19fD////w////8P////D////w////4////4sAAAAAgAF3cwAAOlwAAG5kAABzXAAAc3QAADMyAABiZQAAQzoAAGluAAB3cwAAeXMAAG0zAABXaQAAb3cAAG93gAFTaA=="
			//'http://bitsnoop.com/favicon.ico'
			//'https://translate.google.com/favicon.ico'
		//,yah : "data:image/x-icon;base64,AAABAAEAEBAQAAEABAAoAQAAFgAAACgAAAAQAAAAIAAAAAEABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAbgJqAIoCdgCaAnoAnhKCAKYijgCuLpIAskKeALpSpgC+Yq4AzHy8ANqezgDmvt4A7tLqAPz5+wD///8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAKlRFIoABWAKERERE6ADcKMzzu2hOgAAhERK8REWCWBERE36ERMHMEREvo6iEgY6hEn6Pu0mAzqkz/xjMzoDNwpERERDoAMzAKlERIoAAzMAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAD//wAA//8AAP//AADAOQAAgBkAAAAPAAAACQAAAAkAAAAIAAAACAAAAAgAAIAYAADAOAAA//8AAP//AAD//wAA"
			//'http://www.yahoo.com/favicon.ico'
		,douban : "data:image/x-icon;base64,AAABAAEAEBAAAAEACABoBQAAFgAAACgAAAAQAAAAIAAAAAEACAAAAAAAAAEAABILAAASCwAAAAEAAAABAAA4jSoAEHMAAIW4fQCtz6gAQZIzAODt3gAQcgAARJQ3AFCbRAA3iikA3uzcAKvNpQDL4cgAFHQEADiMKgBfpFQAN4oqAD+OMgCRwIkAQJAyACqDGwBHkzsAR5Y6ABV3BABEkDcARJE3ACqFGwBQmkQA3OvZAIa4fQA2iikAQ5Q2AF+hVADb6tkAcKpmAFCYRABDkDYAkL6JAEiWOwCZxZIAzOHIAIa5fQBHlDoArtCoAJnEkgBwrWYAPo4xADaJKQCszqYAOIsrAIS3fAA4iyoAEXYAABF1AAARdAAA////ABF3AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABDg1NgE2NjY2NjY2NgE2EzgPKwMwCzAwMDALMAMDIDU4Jzc3Nzc3Nzc3Nzc3Nyw0ODg4OBI3IjU4LTclATQ4ODg4ODQFNw02NRc3BQY2NDg4ODgbNzcvLhEeNzcjATU4ODgmNzc3Nzc3Nzc3NxU1ODg4BzchEAAAAAAAHDcYNTg4OB83DAY2NTU1NSg3JDU4ODgHNwoxMTExMTEKNxk1ODg4Fjc3Nzc3Nzc3NzcqNDg4ODQOMwkzMzMzCTMzNjU0OBopHQIyMjIyMjICAgIUNDgINzc3Nzc3Nzc3Nzc3CDg4ODg4ODg4ODg4ODg4ODg4BDg4ODg4ODg4ODg4ODg4BAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA="
			//'http://www.douban.com/favicon.ico'
		,wangyimusic : "data:image/x-icon;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAAAAAABMLAAATCwAAAAAAAAAAAAAAANQGBQXokQUF6O4GBur/Bgbq/wYG6v8GBur/Bgbq/wYG6v8GBur/Bgbq/wYG6v8GBur/BQXo7gUF6JEAANQGBQXokAYG6v8GBur/Bgbq/wYG6v83N+7/pKT3///////u7v7/v7/6/2Zm8v8KCur/Bgbq/wYG6v8GBur/BgboiQUF6O0GBur/Bgbq/wcH6v+KivX//v7///f3/v/i4vz/pqb4/+bm/f//////ysr7/xsb7P8GBur/Bgbq/wUF6O0GBur/Bgbq/wYG6v+IiPX//////7Ky+P8fH+z/Bgbq/wYG6v8LC+r/bGzz//n5///Y2Pz/EhLr/wYG6v8GBur/Bgbq/wYG6v82Nu7//f3//7i4+f8JCer/Bgbq/xAQ6/8GBur/Bgbq/wYG6v9fX/H//////4GB9P8GBur/Bgbq/wYG6v8GBur/oKD3//z8//8jI+z/Bgbq/ycn7f//////6ur9/2Bg8v8GBur/Bwfq/9fX/P/Z2fz/Bgbq/wYG6v8GBur/Bgbq/+bm/f/Fxfr/Bgbq/wYG6v/MzPv/+/v//9PT+//8/P//Ly/t/wYG6v+srPj//f3//wYG6v8GBur/Bgbq/wYG6v/+/v//qKj4/wYG6v8bG+z//////52d9/9HR/D//////2lp8v8GBur/wcH6/+vr/f8GBur/Bgbq/wYG6v8GBur/6en9/729+f8GBur/ExPr//7+//+hoff/cXHz//////9FRe//Ojru//z8//+envf/Bgbq/wYG6v8GBur/Bgbq/62t+P/39/7/Gxvs/wYG6v+2tvn//Pz//76++f/z8/7/XFzx/+zs/f/u7v7/IiLs/wYG6v8GBur/Bgbq/wYG6v9FRe///////6am+P8GBur/Hx/s///////////////////////j4/3/Njbu/wYG6v8GBur/Bgbq/wYG6v8GBur/Bgbq/56e9///////n5/3/xIS6/+CgvT//////7Oz+f9jY/L/EBDr/wYG6v8GBur/Bgbq/wYG6v8GBur/Bgbq/wYG6v8LC+r/np73///////t7f7/hob1//////8nJ+3/CAjq/xQU6/8GBur/Bgbq/wYG6v8GBur/BQXo7QYG6v8GBur/Bgbq/wYG6v9MTPD/sLD4/2pq8v//////t7f5/9HR+//w8P7/CAjq/wYG6v8GBur/BQXo7QUF6JAGBur/Bgbq/wYG6v8GBur/Bgbq/wYG6v8KCur/lpb2//T0/v/g4Pz/aGjy/wYG6v8GBur/Bgbq/wYG6IgAANQGBQXokQUF6O0GBur/Bgbq/wYG6v8GBur/Bgbq/wYG6v8GBur/Bgbq/wYG6v8GBur/BQXo7gUF6JEAANQGAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=="
		    //'http://s1.music.126.net/music.ico'
		,qqvideo : "data:image/ico;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAQAQAABMLAAATCwAAAAAAAAAAAAAAAAAAAAAAAAAAAADFfyS9yIUl/8CPH//IiCX/sHwi65pmGLOYZxdDAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAANh51cOXMf4xX8l/tCfLP/NoS7/1KMr/9SjK//Omyz/mmcY5ppmGHUAAAAAAAAAAAAAAAAAAAAAAAAAAANg6mICXdT7D2bI/zGiWf8GsmH/BbZi/2itSf/CjS7/16Yq/9KfK/+lbxv2i2YvvQAAAAAAAAAAAAAAAAAAAAAIVLPLA2fv/wxl1P8GsmH/AZ5P/wKZSf8Dx2z/Lrpg/8OOLf/Nni7/0qMs/6tyFP+FWiXDAAAAAAAAAAAAAAAABFTG6gFk6f8LZNj/ALJc/wGTRf+r28r/BLFb/wPBaf8OuWP/vYot/9KjLP/Wpiv/vIgg/4VeKrwAAAAAAAAAAAFU1P8CYuT/CWLb/wC4W/8Bk0X/+/38/+ny7/8kqWv/A8No/wPDbv+2kTX/0qEv/9mpKf/RoSr/kmYqzwAAAAABU9L7BWPs/wlj3v8Aulb/AZNF/9/p5v/X5N//3Ojk/wKsWv8Dv2n/Bbpp/8SRLf/dsyr/6swp/9q0Lv/Ijy7XAVXV+wWF/f8Kcub/AcVh/wGTRf/7/Pz/+/38//z8/P/7/fz/Ardj/wDQef8B0n///swi//7iFv/60zv/ypcz/gFh4PsFkf7/Cnju/wHEX/8Bk0X//P39//v8/P/7/Pz/7/r3/wKsWv8A0Xz/AuyU//7MIv/+6B///NZT/86sL6cBZun5BZ3//wWa/f8CzWT/AZNF//z9/f/7/Pz/9fv5/wKrXf8A1oL/AuyU//7MIv/75yL//fFE/86sL/cAAAAAAWHj+AW4//8Gpfv/A9dw/wGTRf/u+fT/eODA/wCvXf8CzG7/AuyU//7MIv/56CP//f9A/9GrMv8AAAAAAAAAAARj3fQFuP//BbP//wPQcf8Bk0X/lOPL/wGwX/8K03//AuyU//7MIv/+6SL/++sp/9SnL/8AAAAAAAAAAAAAAAADQomaBbj//wW4//8CzGv/BNR+/wa5Yv8C7JT/AuyU//7MIv/+6SL//OUg/9eyKv8AAAAAAAAAAAAAAAAAAAAAAGDkMBZ83PwFpP//CM1x/wLslP8C7JT/AuyU//7pIv/+6SL/58Qt/s2vI/AAAAAAAAAAAH9/fwIAAAAAAAAAAAAAAAAAYOQwFobW/OSrKPL/y2T//uki//7pIv/t1iP/2bgc+82vJF0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADmqyhS4Lkn+NeuH//RpyDsuHkMaQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA4H9FU4AfUl8AD1ZFAAc2AAADT0MAAVNPAABSRQAAU0kAAD0xAAFhAAADb2cAB21EAA9hPYAfXFDAP2dy4P9EYQ=="
		    //'http://v.qq.com/favicon.ico'
		,bing : "data:image/ico;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAQAQAABMLAAATCwAAAAAAAAAAAAAAuf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Dtvr/Abj9/wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8dlMH/TFZa/0dcZf8al8f/ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8zdY7/UFBQ/1BQUP9QUFD/UFBQ/zptgf8MqeT/ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf7/QmJu/zN3kf9PUVL/UFBQ/1BQUP9QUFD/TlJT/yuBov8DtPf/ALn//wC5//8Auf//ALn//wC5//8Auf//ALn+/1BQUP9FXmf/FZ3R/zR0jP9QUFH/UFBQ/1BQUP9QUFD/R1xj/xyVw/8Auf//ALn//wC5//8Auf//ALn//wC5/v9QUFD/UFBQ/0Nhbf8Auf//D6Xd/zlug/9QUFD/UFBQ/1BQUP9QUFD/ALn+/wC5//8Auf//ALn//wC5//8Auf7/UFBQ/1BQUP9QUFD/ALn//wC5//8Fs/X/NnKI/1BQUP9QUFD/UFBQ/wC5/v8Auf//ALn//wC5//8Auf//ALn+/1BQUP9QUFD/UFBQ/wC5//8Auf//TFVZ/1BQUP9QUFD/UFBQ/1BQUP8Auf7/ALn//wC5//8Auf//ALn//wC5/v9QUFD/UFBQ/1BQUP8Auf//MXmU/1BQUP9QUFD/R1xk/y58mf8WndD/ALn//wC5//8Auf//ALn//wC5//8Auf7/UFBQ/1BQUP9QUFD/ALn//z9ndv8ohKf/D6Xd/wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn+/1BQUP9QUFD/UFBQ/wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5/v9QUFD/UFBQ/0ZdZf8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf7/UFBQ/0NhbP8nhqv/ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wO09/8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//ALn//wC5//8Auf//AABOVAAASUUAAEluAABsNgAARmEAAGx5AAAgTQAAZWwAADUgAABlcAAAbmcAACwgAABudQAAZUkAAGVsAABSTw=="
		//,baidu : "data:image/ico;base64,AAABAAEAEBAAAAEACABoBQAAFgAAACgAAAAQAAAAIAAAAAEACAAAAAAAQAEAABMLAAATCwAAAAEAAAAAAAAAAAAA////AOEyKQD1vrsA4jcuAPOvrADxnJgA7YR/AP/9/ADpbGUA5lRMAPfIxQD1u7kA/e7tAOt2bwDoZV4A98XDAPjPzQDpZ2AA+uDeAOx9dwD51NIA/fHwAOx6dQDypqIA/OnoAO6OiQD63dwA5EU9APKopADiOTEA+dbUAOdZUQDnW1QA++TjAP749wDsf3oA9LezAPvi4QDjPjYA5U9HAOlpYwD2wL4A/OzrAOddVgDoYlsA/fPyAPGhnQDyo58A7ouGAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgICAgICAgICAgICAgICAgIBAQEBAQEBAQEBAQEBAQICAQEuCQIoMRogAg8uAQECAgEBGAICAgICAgICLwEBAgIBAS8CAgICAgICAjABAQICAQEWKAICAgICAi0uAQECAgEBASsoAgICAiwjAQEBAgIBCCUfJicCAigNKQQqAQICARgCHhYfICEiIwICJAECAgEaAgIbAQEBAQEcAh0BAgIBEQISExQVFhcYGQsBAQICAQENAQ4CDwUCAhABAQECAgEBAQEJAgoLAgIMAQEBAgIBAQEBAwQFAQYHCAEBAQICAQEBAQEBAQEBAQEBAQECAgICAgICAgICAgICAgICAgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA="
			//'http://www.baidu.com/favicon.com'
		,config : "data:image/png;base64,AAABAAEAEBAAAAEAIABoBAAAFgAAACgAAAAQAAAAIAAAAAEAIAAAAAAAQAQAABILAAASCwAAAAAAAAAAAAAAAAAAAAAAAAAAAAsAAAAcAAAAFQAAAB0AAAAvAAAAMAAAADEAAAAvAAAAGgAAABEAAAAWAAAABgAAAAAAAAAAAAAAAAAAAAIAAAATAAAAJQgLC2cGCAhxAAAAQllOTe5cUVD1AAAARQYICG0KDAxYAAAAGgAAAAsAAAAAAAAAAAAAAAAAAAAAAAAAAAsODwZ5amfrbl9d6A8ZGnCKbWn/i25q/w8ZGm5vYF/oempp6QsODgUAAAAAAAAAAAAAAAAAAAAAAAAAACotLgEAAAAAdmxrw6N/ev+fhYH/spaR/7GVkP+ehID/o356/3Zsa8IAAAAAKi0uAQAAAAAAAAAAAAAAAGprbB+Mf33udWtqxnpoZeS9nZj/0LWx/8Oppf/EqaX/0bWx/72cmP95aGbjd21sxY1/fe5qa2wfAAAAAAAAAABYWloUiX5837ealf/AoJz/yLKv/8Sqpf+2npr/tp6a/8arpv/Ks7D/wKGc/7eZlP+Ifn3fWFpaFAAAAAAAAAAAAAAAAEtRU1epkY3/zrCq/8Soo/+1pqT/xMjJlsTJypa0pqT/xamk/86vqv+qk4//TFNUXQAAAAAAAAAAYmNjOpCJh+O+q6j/waWh/8apo/+6oJv/lJOTlwAAAAAAAAAAmJmZkLaemf/HqqT/wqah/72rqP+QiIfiAAAAAFBQUTqTjIvjz8G//866tf/Gq6X/zLGs/3p5eZMAAAAAAAAAAG9tbo/Os67/xaqk/8+6tf/Mv7z/lI2M2wAAAAAAAAAAAAAAAGltb02+rKj/yK+p/9i/uv/Br6z/b21tmHZzc5vFs6//1b22/8atp//Arqv/Z2ttUAAAAAAAAAAAAAAAAJWWlxm1qqjh59PO/9vIw/+tm5b/28O9/+zUzv/r083/1L23/6yblv/ey8b/5dHN/7Sqp+CWl5cZAAAAAAAAAACFgIAjvLWy8K+sq8bGv73k2MXA/7imoP+2pJ//tqSf/72qpf/dy8X/vbm4ya2rq7O9tbP1hX9/IwAAAAAAAAAAAAAAAImKiwIAAAAAsaqoyfzs5v/b0tD/1MfD/9THw//a09D/+Ojj/6+oprkAAAAAiYqLBQAAAAAAAAAAAAAAAAAAAAAAAAAAkZSUBsbAve3Bu7rfg4WHVuPe2v/i3dn+f4KESMG8utvIwL3zkZOTCQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACXmJgglZSVFwAAAAC7trTcvbi25gAAAACVlZUWl5iYIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAgAM3MIABUHLgB3Jh8A9hdMADQzrAA3JvwANhbYGBdGGBgXJvwANhbcADbGXAA0M68A9yb/APYW3+f2ls//8AUA==" 

	};

	engArr = [
		 {on:1, name:'Google中文', icon:icons.google, type:0, kwI:'q=', url1:'www.google.', url2:'', urlS:'https://www.google.com/search?filter=0&lr=lang_zh-CN&q=--keywords--'}
		,{on:0, name:'Google Images', icon:icons.goo, type:1, kwI:'q=', url1:'www.google.', url2:'/images?', urlS:'https://www.google.com/images?q=--keywords--'}
		,{on:0, name:'Google Video', icon:icons.goo, type:2, kwI:'q=', url1:'www.google.', url2:'&tbs=vid:1', urlS:'http://www.google.com/search?q=--keywords--&tbs=vid:1'}
		,{on:0, name:'Google News', icon:icons.goo, type:3, kwI:'q=', url1:'www.google.', url2:'&tbs=nws:1', urlS:'http://www.google.com/search?q=--keywords--&tbs=nws:1'}
		,{on:0, name:'Google Shopping', icon:icons.goo, type:4, kwI:'q=', url1:'www.google.', url2:'/products?', urlS:'http://www.google.com/products?q=--keywords--'}
		,{on:0, name:'Google Blog', icon:icons.goo, type:5, kwI:'q=', url1:'www.google.', url2:'&tbs=blg:1', urlS:'http://www.google.com/search?q=--keywords--&tbs=blg:1'}
		,{on:0, name:'Google Maps', icon:icons.goo, type:6, kwI:'q=', url1:'maps.google.', url2:'', urlS:'http://maps.google.com/maps?q=--keywords--'}
		,{on:1, name:'必应', icon:icons.bing, type:0, kwI:'q=', url1:'bing.com', url2:'', urlS:'https://www.bing.com/search?q=--keywords--'}
		,{on:1, name:'维基百科', icon:icons.wikipedia, type:0, kwI:'wd=', url1:'.wikipedia.org', url2:'', urlS:'https://zh.wikipedia.org/w/index.php?search=--keywords--&title=Special:Search&profile=all'}
		,{on:1, name:'Youtube', icon:icons.youtube, type:0, kwI:'q=', url1:'www.youtube.com', url2:'', urlS:'https://www.youtube.com/results?search_filter=0&search_query=--keywords--'}
		,{on:1, name:'Google翻译', icon:icons.googletrans, type:0, kwI:'q=', url1:'translate.google.com', url2:'', urlS:'https://translate.google.com/?source=osdd#auto|auto|--keywords--'}
		,{on:1, name:'Twitter', icon:icons.twitter, type:0, kwI:'q=', url1:'twitter.com', url2:'', urlS:'https://twitter.com/search?q=--keywords--'}
		,{on:0, name:'WolframAlpha', icon:icons.wolfa, type:0, kwI:'i=', url1:'wolframalpha.com', url2:'', urlS:'https://www.wolframalpha.com/input/?i=--keywords--&dataset='}
		,{on:1, name:'亚马逊', icon:icons.amazon, type:0, kwI:'keywords=', url1:'z.cn', url2:'', urlS:'https://www.amazon.cn/s/keywords=--keywords--'}
		,{on:1, name:'豆瓣电影', icon:icons.douban, type:0, kwI:'q=', url1:'douban.com', url2:'', urlS:'https://movie.douban.com/subject_search?search_text=--keywords--'}
		,{on:1, name:'网易音乐', icon:icons.wangyimusic, type:0, kwI:'q=', url1:'music.163.com', url2:'', urlS:'http://music.163.com/#/search/m/?s=--keywords--&type=10'}
        ,{on:1, name:'腾讯视频', icon:icons.qqvideo, type:0, kwI:'ms_key=', url1:'v.qq.com', url2:'', urlS:'http://v.qq.com/search.html?ms_key=--keywords--'}
		,{on:0, name:'海盗湾', icon:icons.tpb, type:0, kwI:'q=', url1:'thepiratebay.org', url2:'', urlS:'https://thepiratebay.org/s/?q=--keywords--&category=0&page=0&orderby=99'}
		,{on:1, name:'BitSnoop', icon:icons.bts, type:0, kwI:'q=', url1:'bitsnoop.com', url2:'', urlS:'http://bitsnoop.com/search?q=--keywords--&t=all'}
	];
	



//'贴 吧','http://tieba.baidu.com/f?ct=318767104&tn=baiduKeywordSearch&rn=50&pn=0&rs2=0&myselectvalue=1&submit=????&tb=on&ie=utf-8&word=--keywords--'
//'知 道','http://zhidao.baidu.com/q?word=--keywords--&ie=utf-8&ct=17&pn=0&pt=monline_ik&tn=ikaslist&rn=10'
//图书 http://book.baidu.com/s?tn=baidubook&ct=2097152&si=book.baidu.com&cl=3&ie=utf-8&wd=--keywords--
//books http://www.google.com/search?q=--keywords--&tbs=bks:1
//schol http://scholar.google.com/scholar?q=--keywords--
// 'Yahoo',  'p', 'yahoo.',      'http://search.yahoo.com/search/dir?p=--keywords--'
// 'Clusty', 'query', 'clusty.', 'http://clusty.com/search?query=--keywords--'
// 'Wolfram', 'i', 'wolframalpha.', 'http://www01.wolframalpha.com/input/?i=--keywords--'
	
// ## Customiztion ends | 自定义区结束 ##

//searchenginearray.sort();

//var r = escape(document.referrer);
//var u = escape(document.location.href);
var u = document.location.href;
var b = document.getElementById('sjaSideBar');
var d = document.location.host;
var q = document.location.search.slice(1);
var e = -1;

var keywords = '';

for (i = 0; i < engArr.length; i++) {
	if ((d.indexOf(engArr[i].url1) != -1) && ((!engArr[i].url2) || (!!engArr[i].url2 && u.indexOf(engArr[i].url2) != -1))) {
		e = i;
	}
}
//fix Google Image Search url (Google playing shitty cards?)
if ((d.indexOf('www.google.') != -1) && (u.indexOf('&tbm=isch') != -1)) {
	e = 1;
}

//l(e);
if ((q.length > 0) && (e != -1)) {
	// There's a querystring and it's a search referral
	if (engArr[e].name.indexOf('百度') == 0 && q.indexOf('ie=utf-8') == -1) {  // 如果是百度且非utf-8
		keywords = getBaiduWord();
	}
	else {
		var qspairs = q.split('&');
		for (k = 0; k < qspairs.length; k++) {
			if (qspairs[k].indexOf(engArr[e].kwI) == 0) {keywords = qspairs[k].substring(engArr[e].kwI.length); break;}
		}
	}
}
//l(keywords);
if (!keywords) return;

// Insert CSS
var headID = document.getElementsByTagName("head")[0];         
var cssNode = creaElemIn('style', headID);
cssNode.type = 'text/css';
cssNode.innerHTML = '#sjaSideBar {width:'+((lt)?'28px;_left:-16px':'12px;right:0')+';padding:5px 5px;overflow:hidden;z-index:1000;opacity:.6;_border:1px solid #C5CCD9;_border-color: rgba(82,168,236,0.8);_border-radius: 2px;_box-shadow: 2px 2px 15px #999;border-'+((lt)?'left':'right')+':0;}\
		#sjaSideBar:hover {width:28px;opacity:1;'+((lt)?'left:0;':'')+'} \
		#sjaSideBar>a {text-align:left;white-space:nowrap;text-decoration:none;margin: 0 3px 3px 3px;padding: 3px 8px 3px 2px;display:block;color:#00c;font-size:14px;outline:none;} \
		#sjaSideBar>input {text-align:middle;margin:3px 3px;padding:1px 3px;color:black;font-size:14px;border:1px solid #1599BF;outline:none;} \
		#sjaSideBar>a>div {height:22px;width:22px;} \
		#sjaSideBar, #sjaTitleBox {position:fixed; _-webkit-box-shadow: inset 0 1px 0 rgba(255,255,255,.2), 0 1px 2px rgba(0,0,0,.05);} \
		_#sjaSideBar:hover, _#sjaTitleBox {_background-image: linear-gradient(to bottom, #ffffff, #e6e6e6); _border: 1px solid #bbbbbb; border-radius: 3px; -webkit-box-shadow: inset 0 1px 0 rgba(255,255,255,.2), 0 1px 2px rgba(0,0,0,.05);border-'+((lt)?'left':'right')+':0;} \
		#sjaTitleBox:before { right: 0; left: -16px; border: solid transparent; content: " "; height: 0; width: 0; position: absolute; pointer-events: none; border-width: 8px; top: 50%; margin-top: -8px; border-right-color: #ffa500; } \
		#sjaTitleBox {font-size:16px;text-align:'+((lt)?'left':'right')+';line-height:26px;padding:3px 5px;_padding-'+((!lt)?'left':'right')+':2px;height:26px;'+((lt)?'left':'right')+':38px;z-index:1000;display:none;} \
		#sjaTitleBox { position: fixed; color: #fff; background: #ffa500; _background-image: linear-gradient(to bottom, #aaa, #555); _border: 1px solid #777; border-radius: 5px; -webkit-box-shadow: inset 0 1px 0 rgba(255,255,255,.2), 0 1px 2px rgba(0,0,0,.05); } \
		_#sjaTitleBox {background-image: linear-gradient(to bottom, #ffffff, #e6e6e6); border: 1px solid #bbbbbb; border-radius: 3px; -webkit-box-shadow: inset 0 1px 0 rgba(255,255,255,.2), 0 1px 2px rgba(0,0,0,.05);} \
		#sjaSideBar:hover #sjaTitleBox {display:block;}';
	
if (!b) make_boxes();

function make_boxes() {
	b = creaElemIn("div", document.body);
	b.id = 'sjaSideBar';
	b.style.top = tp + 'px';
	
	var j=-1;

	for (i = 0; i < engArr.length; i++) {
		if (engArr[i].on != 1 || engArr[i].type != engArr[e].type || (engArr[i].on == 1 && engArr[i].type != engArr[e].type && engArr[i].type != -1)) continue;
		j++; //another index
	// links	
		lg[i] = creaElemIn("a", b);
		lg[i].href = engArr[i].urlS.replace('--keywords--', keywords);
		lg[i].target = (nw)?'nw':'_top';
		// lg[i].title = engArr[i].name;
		lg[i].id = i;
		lg[i].name = j;
	// show tooltip	
		lg[i].addEventListener("mouseover", function(e){
				// this_y = getY(this);
				this_y = b.offsetTop + 3 + 31*this.name;
				this_title = engArr[this.id].name;
				if (!titlebox) {
					titlebox = creaElemIn("div", b);
					titlebox.id = 'sjaTitleBox';
				}
				titlebox.innerHTML = this_title;
				titlebox.style.top = this_y +'px';
			}, false);
	// favicon	
		favImg[i] = creaElemIn("div", lg[i]);
		favImg[i].style.background = 'url("' + engArr[i].icon + '") 1px center no-repeat';
	}
	config_btn = creaElemIn("a", b);
	var config_btn_img = creaElemIn("div", config_btn);
	config_btn_img.style.background = 'url("' + icons.config + '") 1px center no-repeat';
	config_btn.title = 'Search Jump Around 设置';
	config_btn.addEventListener('click',config_box,false);
}

function config_box() {//l(nw,lt,tp);
	config_btn.disabled = true;
	var confBOXBack = creaElemIn('div', document.body);
		confBOXBack.id = 'sjaConfigBack';
		confBOXBack.setAttribute('style', 'background:rgba(255,255,255,.7);position:fixed;top:0;left:0;width:100%;height:100%;text-align:center;z-index:9999;');
	var confBOX = creaElemIn('div', confBOXBack);
		confBOX.setAttribute('style', 'width:300px;background:white;line-height:18px;border:2px solid #1599BF;margin:150px auto auto auto;padding:5px;');
	var confTitle = creaElemIn('h3', confBOX);
		confTitle.setAttribute('style', 'font-weight:800;border-bottom:1px solid #1599BF;margin:15px auto 10px auto;line-height:24px;');
		confTitle.innerHTML = 'Search Jump Around 设置';
	var confP = creaElemIn('p', confBOX);
		confP.setAttribute('style', 'text-align:left;');
	var conf = [], confR = [], confL = [], opt;
	var confT = ['跳转链接是否默认在新窗口打开？','跳转条显示在左边还是右边？','跳转条的顶部高度：'];
	var confRT = [['否','是'],['右','左']];
	for (n=0;n