#include "wifi.h"

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

char indexHtml[] = "<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"<head>\n"
"    <meta charset=\"UTF-8\">\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
"    <title>LED Steps</title>\n"
"    <!-- Pure.css -->\n"
"    <style>\n"
"        html{line-height:1.15;-webkit-text-size-adjust:100%}body{margin:0}main{display:block}h1{font-size:2em;margin:.67em 0}hr{-webkit-box-sizing:content-box;box-sizing:content-box;height:0;overflow:visible}pre{font-family:monospace,monospace;font-size:1em}a{background-color:transparent}abbr[title]{border-bottom:none;text-decoration:underline;-webkit-text-decoration:underline dotted;text-decoration:underline dotted}b,strong{font-weight:bolder}code,kbd,samp{font-family:monospace,monospace;font-size:1em}small{font-size:80%}sub,sup{font-size:75%;line-height:0;position:relative;vertical-align:baseline}sub{bottom:-.25em}sup{top:-.5em}img{border-style:none}button,input,optgroup,select,textarea{font-family:inherit;font-size:100%;line-height:1.15;margin:0}button,input{overflow:visible}button,select{text-transform:none}[type=button],[type=reset],[type=submit],button{-webkit-appearance:button}[type=button]::-moz-focus-inner,[type=reset]::-moz-focus-inner,[type=submit]::-moz-focus-inner,button::-moz-focus-inner{border-style:none;padding:0}[type=button]:-moz-focusring,[type=reset]:-moz-focusring,[type=submit]:-moz-focusring,button:-moz-focusring{outline:1px dotted ButtonText}fieldset{padding:.35em .75em .625em}legend{-webkit-box-sizing:border-box;box-sizing:border-box;color:inherit;display:table;max-width:100%;padding:0;white-space:normal}progress{vertical-align:baseline}textarea{overflow:auto}[type=checkbox],[type=radio]{-webkit-box-sizing:border-box;box-sizing:border-box;padding:0}[type=number]::-webkit-inner-spin-button,[type=number]::-webkit-outer-spin-button{height:auto}[type=search]{-webkit-appearance:textfield;outline-offset:-2px}[type=search]::-webkit-search-decoration{-webkit-appearance:none}::-webkit-file-upload-button{-webkit-appearance:button;font:inherit}details{display:block}summary{display:list-item}template{display:none}[hidden]{display:none}html{font-family:sans-serif}.hidden,[hidden]{display:none!important}.pure-img{max-width:100%;height:auto;display:block}.pure-g{letter-spacing:-.31em;text-rendering:optimizespeed;font-family:FreeSans,Arimo,\"Droid Sans\",Helvetica,Arial,sans-serif;display:-webkit-box;display:-ms-flexbox;display:flex;-webkit-box-orient:horizontal;-webkit-box-direction:normal;-ms-flex-flow:row wrap;flex-flow:row wrap;-ms-flex-line-pack:start;align-content:flex-start}@media all and (-ms-high-contrast:none),(-ms-high-contrast:active){table .pure-g{display:block}}.opera-only :-o-prefocus,.pure-g{word-spacing:-.43em}.pure-u{display:inline-block;letter-spacing:normal;word-spacing:normal;vertical-align:top;text-rendering:auto}.pure-g [class*=pure-u]{font-family:sans-serif}.pure-u-1,.pure-u-1-1,.pure-u-1-12,.pure-u-1-2,.pure-u-1-24,.pure-u-1-3,.pure-u-1-4,.pure-u-1-5,.pure-u-1-6,.pure-u-1-8,.pure-u-10-24,.pure-u-11-12,.pure-u-11-24,.pure-u-12-24,.pure-u-13-24,.pure-u-14-24,.pure-u-15-24,.pure-u-16-24,.pure-u-17-24,.pure-u-18-24,.pure-u-19-24,.pure-u-2-24,.pure-u-2-3,.pure-u-2-5,.pure-u-20-24,.pure-u-21-24,.pure-u-22-24,.pure-u-23-24,.pure-u-24-24,.pure-u-3-24,.pure-u-3-4,.pure-u-3-5,.pure-u-3-8,.pure-u-4-24,.pure-u-4-5,.pure-u-5-12,.pure-u-5-24,.pure-u-5-5,.pure-u-5-6,.pure-u-5-8,.pure-u-6-24,.pure-u-7-12,.pure-u-7-24,.pure-u-7-8,.pure-u-8-24,.pure-u-9-24{display:inline-block;letter-spacing:normal;word-spacing:normal;vertical-align:top;text-rendering:auto}.pure-u-1-24{width:4.1667%}.pure-u-1-12,.pure-u-2-24{width:8.3333%}.pure-u-1-8,.pure-u-3-24{width:12.5%}.pure-u-1-6,.pure-u-4-24{width:16.6667%}.pure-u-1-5{width:20%}.pure-u-5-24{width:20.8333%}.pure-u-1-4,.pure-u-6-24{width:25%}.pure-u-7-24{width:29.1667%}.pure-u-1-3,.pure-u-8-24{width:33.3333%}.pure-u-3-8,.pure-u-9-24{width:37.5%}.pure-u-2-5{width:40%}.pure-u-10-24,.pure-u-5-12{width:41.6667%}.pure-u-11-24{width:45.8333%}.pure-u-1-2,.pure-u-12-24{width:50%}.pure-u-13-24{width:54.1667%}.pure-u-14-24,.pure-u-7-12{width:58.3333%}.pure-u-3-5{width:60%}.pure-u-15-24,.pure-u-5-8{width:62.5%}.pure-u-16-24,.pure-u-2-3{width:66.6667%}.pure-u-17-24{width:70.8333%}.pure-u-18-24,.pure-u-3-4{width:75%}.pure-u-19-24{width:79.1667%}.pure-u-4-5{width:80%}.pure-u-20-24,.pure-u-5-6{width:83.3333%}.pure-u-21-24,.pure-u-7-8{width:87.5%}.pure-u-11-12,.pure-u-22-24{width:91.6667%}.pure-u-23-24{width:95.8333%}.pure-u-1,.pure-u-1-1,.pure-u-24-24,.pure-u-5-5{width:100%}.pure-button{display:inline-block;line-height:normal;white-space:nowrap;vertical-align:middle;text-align:center;cursor:pointer;-webkit-user-drag:none;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none;user-select:none;-webkit-box-sizing:border-box;box-sizing:border-box}.pure-button::-moz-focus-inner{padding:0;border:0}.pure-button-group{letter-spacing:-.31em;text-rendering:optimizespeed}.opera-only :-o-prefocus,.pure-button-group{word-spacing:-.43em}.pure-button-group .pure-button{letter-spacing:normal;word-spacing:normal;vertical-align:top;text-rendering:auto}.pure-button{font-family:inherit;font-size:150%;padding:.5em 1em;color:rgba(0,0,0,.8);border:none transparent;background-color:#0078e7;text-decoration:none;border-radius:2px}.pure-button-hover,.pure-button:focus,.pure-button:hover{background: rgb(66, 184, 221);background-image:linear-gradient(transparent,rgba(0,0,0,.05) 40%,rgba(0,0,0,.1))}.pure-button:focus{outline:0}.pure-button-active,.pure-button:active{-webkit-box-shadow:0 0 0 1px rgba(0,0,0,.15) inset,0 0 6px rgba(0,0,0,.2) inset;box-shadow:0 0 0 1px rgba(0,0,0,.15) inset,0 0 6px rgba(0,0,0,.2) inset;border-color:#000}.pure-button-disabled,.pure-button-disabled:active,.pure-button-disabled:focus,.pure-button-disabled:hover,.pure-button[disabled]{border:none;background-image:none;opacity:.4;cursor:not-allowed;-webkit-box-shadow:none;box-shadow:none;pointer-events:none}.pure-button-hidden{display:none}.pure-button-primary,.pure-button-selected,a.pure-button-primary,a.pure-button-selected{color:#fff}.pure-button-group .pure-button{margin:0;border-radius:0;border-right:1px solid rgba(0,0,0,.2)}.pure-button-group .pure-button:first-child{border-top-left-radius:2px;border-bottom-left-radius:2px}.pure-button-group .pure-button:last-child{border-top-right-radius:2px;border-bottom-right-radius:2px;border-right:none}.pure-table{border-collapse:collapse;border-spacing:0;empty-cells:show;border:1px solid #cbcbcb}.pure-table caption{color:#000;font:italic 85%/1 arial,sans-serif;padding:1em 0;text-align:center}.pure-table td,.pure-table th{border-left:1px solid #cbcbcb;border-width:0 0 0 1px;font-size:inherit;margin:0;overflow:visible;padding:.5em 1em}.pure-table thead{background-color:#e0e0e0;color:#000;text-align:left;vertical-align:bottom}.pure-table td{background-color:transparent}.pure-table-odd td{background-color:#f2f2f2}.pure-table-striped tr:nth-child(2n-1) td{background-color:#f2f2f2}.pure-table-bordered td{border-bottom:1px solid #cbcbcb}.pure-table-bordered tbody>tr:last-child>td{border-bottom-width:0}.pure-table-horizontal td,.pure-table-horizontal th{border-width:0 0 1px 0;border-bottom:1px solid #cbcbcb}.pure-table-horizontal tbody>tr:last-child>td{border-bottom-width:0}\n"
"    </style>\n"
"    <!-- Pure.css responsive grid -->\n"
"    <style>\n"
"        @media screen and (min-width:35.5em){.pure-u-sm-1,.pure-u-sm-1-1,.pure-u-sm-1-12,.pure-u-sm-1-2,.pure-u-sm-1-24,.pure-u-sm-1-3,.pure-u-sm-1-4,.pure-u-sm-1-5,.pure-u-sm-1-6,.pure-u-sm-1-8,.pure-u-sm-10-24,.pure-u-sm-11-12,.pure-u-sm-11-24,.pure-u-sm-12-24,.pure-u-sm-13-24,.pure-u-sm-14-24,.pure-u-sm-15-24,.pure-u-sm-16-24,.pure-u-sm-17-24,.pure-u-sm-18-24,.pure-u-sm-19-24,.pure-u-sm-2-24,.pure-u-sm-2-3,.pure-u-sm-2-5,.pure-u-sm-20-24,.pure-u-sm-21-24,.pure-u-sm-22-24,.pure-u-sm-23-24,.pure-u-sm-24-24,.pure-u-sm-3-24,.pure-u-sm-3-4,.pure-u-sm-3-5,.pure-u-sm-3-8,.pure-u-sm-4-24,.pure-u-sm-4-5,.pure-u-sm-5-12,.pure-u-sm-5-24,.pure-u-sm-5-5,.pure-u-sm-5-6,.pure-u-sm-5-8,.pure-u-sm-6-24,.pure-u-sm-7-12,.pure-u-sm-7-24,.pure-u-sm-7-8,.pure-u-sm-8-24,.pure-u-sm-9-24{display:inline-block;letter-spacing:normal;word-spacing:normal;vertical-align:top;text-rendering:auto}.pure-u-sm-1-24{width:4.1667%}.pure-u-sm-1-12,.pure-u-sm-2-24{width:8.3333%}.pure-u-sm-1-8,.pure-u-sm-3-24{width:12.5%}.pure-u-sm-1-6,.pure-u-sm-4-24{width:16.6667%}.pure-u-sm-1-5{width:20%}.pure-u-sm-5-24{width:20.8333%}.pure-u-sm-1-4,.pure-u-sm-6-24{width:25%}.pure-u-sm-7-24{width:29.1667%}.pure-u-sm-1-3,.pure-u-sm-8-24{width:33.3333%}.pure-u-sm-3-8,.pure-u-sm-9-24{width:37.5%}.pure-u-sm-2-5{width:40%}.pure-u-sm-10-24,.pure-u-sm-5-12{width:41.6667%}.pure-u-sm-11-24{width:45.8333%}.pure-u-sm-1-2,.pure-u-sm-12-24{width:50%}.pure-u-sm-13-24{width:54.1667%}.pure-u-sm-14-24,.pure-u-sm-7-12{width:58.3333%}.pure-u-sm-3-5{width:60%}.pure-u-sm-15-24,.pure-u-sm-5-8{width:62.5%}.pure-u-sm-16-24,.pure-u-sm-2-3{width:66.6667%}.pure-u-sm-17-24{width:70.8333%}.pure-u-sm-18-24,.pure-u-sm-3-4{width:75%}.pure-u-sm-19-24{width:79.1667%}.pure-u-sm-4-5{width:80%}.pure-u-sm-20-24,.pure-u-sm-5-6{width:83.3333%}.pure-u-sm-21-24,.pure-u-sm-7-8{width:87.5%}.pure-u-sm-11-12,.pure-u-sm-22-24{width:91.6667%}.pure-u-sm-23-24{width:95.8333%}.pure-u-sm-1,.pure-u-sm-1-1,.pure-u-sm-24-24,.pure-u-sm-5-5{width:100%}}@media screen and (min-width:48em){.pure-u-md-1,.pure-u-md-1-1,.pure-u-md-1-12,.pure-u-md-1-2,.pure-u-md-1-24,.pure-u-md-1-3,.pure-u-md-1-4,.pure-u-md-1-5,.pure-u-md-1-6,.pure-u-md-1-8,.pure-u-md-10-24,.pure-u-md-11-12,.pure-u-md-11-24,.pure-u-md-12-24,.pure-u-md-13-24,.pure-u-md-14-24,.pure-u-md-15-24,.pure-u-md-16-24,.pure-u-md-17-24,.pure-u-md-18-24,.pure-u-md-19-24,.pure-u-md-2-24,.pure-u-md-2-3,.pure-u-md-2-5,.pure-u-md-20-24,.pure-u-md-21-24,.pure-u-md-22-24,.pure-u-md-23-24,.pure-u-md-24-24,.pure-u-md-3-24,.pure-u-md-3-4,.pure-u-md-3-5,.pure-u-md-3-8,.pure-u-md-4-24,.pure-u-md-4-5,.pure-u-md-5-12,.pure-u-md-5-24,.pure-u-md-5-5,.pure-u-md-5-6,.pure-u-md-5-8,.pure-u-md-6-24,.pure-u-md-7-12,.pure-u-md-7-24,.pure-u-md-7-8,.pure-u-md-8-24,.pure-u-md-9-24{display:inline-block;letter-spacing:normal;word-spacing:normal;vertical-align:top;text-rendering:auto}.pure-u-md-1-24{width:4.1667%}.pure-u-md-1-12,.pure-u-md-2-24{width:8.3333%}.pure-u-md-1-8,.pure-u-md-3-24{width:12.5%}.pure-u-md-1-6,.pure-u-md-4-24{width:16.6667%}.pure-u-md-1-5{width:20%}.pure-u-md-5-24{width:20.8333%}.pure-u-md-1-4,.pure-u-md-6-24{width:25%}.pure-u-md-7-24{width:29.1667%}.pure-u-md-1-3,.pure-u-md-8-24{width:33.3333%}.pure-u-md-3-8,.pure-u-md-9-24{width:37.5%}.pure-u-md-2-5{width:40%}.pure-u-md-10-24,.pure-u-md-5-12{width:41.6667%}.pure-u-md-11-24{width:45.8333%}.pure-u-md-1-2,.pure-u-md-12-24{width:50%}.pure-u-md-13-24{width:54.1667%}.pure-u-md-14-24,.pure-u-md-7-12{width:58.3333%}.pure-u-md-3-5{width:60%}.pure-u-md-15-24,.pure-u-md-5-8{width:62.5%}.pure-u-md-16-24,.pure-u-md-2-3{width:66.6667%}.pure-u-md-17-24{width:70.8333%}.pure-u-md-18-24,.pure-u-md-3-4{width:75%}.pure-u-md-19-24{width:79.1667%}.pure-u-md-4-5{width:80%}.pure-u-md-20-24,.pure-u-md-5-6{width:83.3333%}.pure-u-md-21-24,.pure-u-md-7-8{width:87.5%}.pure-u-md-11-12,.pure-u-md-22-24{width:91.6667%}.pure-u-md-23-24{width:95.8333%}.pure-u-md-1,.pure-u-md-1-1,.pure-u-md-24-24,.pure-u-md-5-5{width:100%}}@media screen and (min-width:64em){.pure-u-lg-1,.pure-u-lg-1-1,.pure-u-lg-1-12,.pure-u-lg-1-2,.pure-u-lg-1-24,.pure-u-lg-1-3,.pure-u-lg-1-4,.pure-u-lg-1-5,.pure-u-lg-1-6,.pure-u-lg-1-8,.pure-u-lg-10-24,.pure-u-lg-11-12,.pure-u-lg-11-24,.pure-u-lg-12-24,.pure-u-lg-13-24,.pure-u-lg-14-24,.pure-u-lg-15-24,.pure-u-lg-16-24,.pure-u-lg-17-24,.pure-u-lg-18-24,.pure-u-lg-19-24,.pure-u-lg-2-24,.pure-u-lg-2-3,.pure-u-lg-2-5,.pure-u-lg-20-24,.pure-u-lg-21-24,.pure-u-lg-22-24,.pure-u-lg-23-24,.pure-u-lg-24-24,.pure-u-lg-3-24,.pure-u-lg-3-4,.pure-u-lg-3-5,.pure-u-lg-3-8,.pure-u-lg-4-24,.pure-u-lg-4-5,.pure-u-lg-5-12,.pure-u-lg-5-24,.pure-u-lg-5-5,.pure-u-lg-5-6,.pure-u-lg-5-8,.pure-u-lg-6-24,.pure-u-lg-7-12,.pure-u-lg-7-24,.pure-u-lg-7-8,.pure-u-lg-8-24,.pure-u-lg-9-24{display:inline-block;letter-spacing:normal;word-spacing:normal;vertical-align:top;text-rendering:auto}.pure-u-lg-1-24{width:4.1667%}.pure-u-lg-1-12,.pure-u-lg-2-24{width:8.3333%}.pure-u-lg-1-8,.pure-u-lg-3-24{width:12.5%}.pure-u-lg-1-6,.pure-u-lg-4-24{width:16.6667%}.pure-u-lg-1-5{width:20%}.pure-u-lg-5-24{width:20.8333%}.pure-u-lg-1-4,.pure-u-lg-6-24{width:25%}.pure-u-lg-7-24{width:29.1667%}.pure-u-lg-1-3,.pure-u-lg-8-24{width:33.3333%}.pure-u-lg-3-8,.pure-u-lg-9-24{width:37.5%}.pure-u-lg-2-5{width:40%}.pure-u-lg-10-24,.pure-u-lg-5-12{width:41.6667%}.pure-u-lg-11-24{width:45.8333%}.pure-u-lg-1-2,.pure-u-lg-12-24{width:50%}.pure-u-lg-13-24{width:54.1667%}.pure-u-lg-14-24,.pure-u-lg-7-12{width:58.3333%}.pure-u-lg-3-5{width:60%}.pure-u-lg-15-24,.pure-u-lg-5-8{width:62.5%}.pure-u-lg-16-24,.pure-u-lg-2-3{width:66.6667%}.pure-u-lg-17-24{width:70.8333%}.pure-u-lg-18-24,.pure-u-lg-3-4{width:75%}.pure-u-lg-19-24{width:79.1667%}.pure-u-lg-4-5{width:80%}.pure-u-lg-20-24,.pure-u-lg-5-6{width:83.3333%}.pure-u-lg-21-24,.pure-u-lg-7-8{width:87.5%}.pure-u-lg-11-12,.pure-u-lg-22-24{width:91.6667%}.pure-u-lg-23-24{width:95.8333%}.pure-u-lg-1,.pure-u-lg-1-1,.pure-u-lg-24-24,.pure-u-lg-5-5{width:100%}}@media screen and (min-width:80em){.pure-u-xl-1,.pure-u-xl-1-1,.pure-u-xl-1-12,.pure-u-xl-1-2,.pure-u-xl-1-24,.pure-u-xl-1-3,.pure-u-xl-1-4,.pure-u-xl-1-5,.pure-u-xl-1-6,.pure-u-xl-1-8,.pure-u-xl-10-24,.pure-u-xl-11-12,.pure-u-xl-11-24,.pure-u-xl-12-24,.pure-u-xl-13-24,.pure-u-xl-14-24,.pure-u-xl-15-24,.pure-u-xl-16-24,.pure-u-xl-17-24,.pure-u-xl-18-24,.pure-u-xl-19-24,.pure-u-xl-2-24,.pure-u-xl-2-3,.pure-u-xl-2-5,.pure-u-xl-20-24,.pure-u-xl-21-24,.pure-u-xl-22-24,.pure-u-xl-23-24,.pure-u-xl-24-24,.pure-u-xl-3-24,.pure-u-xl-3-4,.pure-u-xl-3-5,.pure-u-xl-3-8,.pure-u-xl-4-24,.pure-u-xl-4-5,.pure-u-xl-5-12,.pure-u-xl-5-24,.pure-u-xl-5-5,.pure-u-xl-5-6,.pure-u-xl-5-8,.pure-u-xl-6-24,.pure-u-xl-7-12,.pure-u-xl-7-24,.pure-u-xl-7-8,.pure-u-xl-8-24,.pure-u-xl-9-24{display:inline-block;letter-spacing:normal;word-spacing:normal;vertical-align:top;text-rendering:auto}.pure-u-xl-1-24{width:4.1667%}.pure-u-xl-1-12,.pure-u-xl-2-24{width:8.3333%}.pure-u-xl-1-8,.pure-u-xl-3-24{width:12.5%}.pure-u-xl-1-6,.pure-u-xl-4-24{width:16.6667%}.pure-u-xl-1-5{width:20%}.pure-u-xl-5-24{width:20.8333%}.pure-u-xl-1-4,.pure-u-xl-6-24{width:25%}.pure-u-xl-7-24{width:29.1667%}.pure-u-xl-1-3,.pure-u-xl-8-24{width:33.3333%}.pure-u-xl-3-8,.pure-u-xl-9-24{width:37.5%}.pure-u-xl-2-5{width:40%}.pure-u-xl-10-24,.pure-u-xl-5-12{width:41.6667%}.pure-u-xl-11-24{width:45.8333%}.pure-u-xl-1-2,.pure-u-xl-12-24{width:50%}.pure-u-xl-13-24{width:54.1667%}.pure-u-xl-14-24,.pure-u-xl-7-12{width:58.3333%}.pure-u-xl-3-5{width:60%}.pure-u-xl-15-24,.pure-u-xl-5-8{width:62.5%}.pure-u-xl-16-24,.pure-u-xl-2-3{width:66.6667%}.pure-u-xl-17-24{width:70.8333%}.pure-u-xl-18-24,.pure-u-xl-3-4{width:75%}.pure-u-xl-19-24{width:79.1667%}.pure-u-xl-4-5{width:80%}.pure-u-xl-20-24,.pure-u-xl-5-6{width:83.3333%}.pure-u-xl-21-24,.pure-u-xl-7-8{width:87.5%}.pure-u-xl-11-12,.pure-u-xl-22-24{width:91.6667%}.pure-u-xl-23-24{width:95.8333%}.pure-u-xl-1,.pure-u-xl-1-1,.pure-u-xl-24-24,.pure-u-xl-5-5{width:100%}}\n"
"    </style>\n"
"    <!-- custom -->\n"
"    <style>\n"
"        .container {\n"
"            margin: auto;\n"
"            width: 30%;\n"
"            padding: 10px;\n"
"        }\n"
"        input[type=\"color\" i] {\n"
"            margin: 4%;\n"
"            width: 300px;\n"
"            height: 200px;\n"
"        }\n"
"        input[type=\"range\" i] {\n"
"            margin: 4%;\n"
"            width: 100%;\n"
"        }\n"
"        .pure-g {\n"
"            margin: 4%;\n"
"        }\n"
"        .pure-u-1 {\n"
"            display: grid;\n"
"            justify-content: center;\n"
"        }\n"
"        .text {\n"
"            height: 0.2cm;\n"
"        }\n"
"    </style>\n"
"</head>\n"
"<body>\n"
"    <div class=\"container\">\n"
"        <div class=\"pure-g\">\n"
"            <div class=\"pure-u-1 pure-u-md-1-3\">\n"
"                <button id=\"auto\" class=\"pure-button pure-button-primary\">Automatic</button>\n"
"            </div>\n"
"            <div class=\"pure-u-1 pure-u-md-1-3\">\n"
"                <button id=\"manual\" class=\"pure-button pure-button-primary\">Manual</button>\n"
"            </div>\n"
"            <div class=\"pure-u-1 pure-u-md-1-3\">\n"
"                <button id=\"off\" class=\"pure-button pure-button-primary\">Off</button>\n"
"            </div>\n"
"        </div>\n"
"        <div class=\"pure-g\">\n"
"            <div class=\"pure-u-1 pure-u-md-1-2\">\n"
"                <label for=\"tlength\">Timer Length</label>\n"
"                <input type=\"number\" step=\".1\" id=\"tlength\">\n"
"            </div>\n"
"            <div class=\"pure-u-1 pure-u-md-1-2\">\n"
"                <label for=\"dlength\">Delay Length</label>\n"
"                <input type=\"number\" step=\".1\" id=\"dlength\">\n"
"            </div>\n"
"        </div>\n"
"        <div class=\"pure-g\">\n"
"            <div class=\"pure-u-1 text\">\n"
"                <h3>Brightness</h3>\n"
"            </div>\n"
"        </div>\n"
"        <div class=\"pure-g\">\n"
"            <input type=\"range\" min=\"0\" max=\"255\" class=\"slider\" id=\"bright\">\n"
"        </div>\n"
"        <div class=\"pure-g\">\n"
"            <div class=\"pure-u-1\">\n"
"                <input type=\"color\" id=\"color\" width=\"100px\" height=\"100px\">\n"
"            </div>\n"
"        </div>\n"
"    </div>\n"
"    <script>\n"
"        window.onload = function () {\n"
"            const boolsEl = {auto: document.getElementById('auto'), manual: document.getElementById('manual'), off: document.getElementById('off')};\n"
"            const colorEl = document.getElementById('color');\n"
"            const brightEl = document.getElementById('bright');\n"
"            const lengthEl = {timer: document.getElementById('tlength'), delay: document.getElementById('dlength')};\n"
"            let buttons = {auto: 1, manual: 0, off: 0};\n"
"            let lengths = {timer: 0.0, delay: 0.0};\n"
"            let color = '#ff1100';\n"
"            let bright = 255;\n"
"            let cacheLengths = {timer: 0.0, delay: 0.0};\n"
"            let cacheColor = '#ff1100';\n"
"            let cacheBright = 255;\n"
"            let timer = setInterval(function () {\n"
"                httpGetAsync('/read', function (call) {\n"
"                    const json = JSON.parse(call);\n"
"                    buttons.auto = json.auto;\n"
"                    buttons.manual = json.manual;\n"
"                    buttons.off = json.off;\n"
"                    lengths.timer = json.timer;\n"
"                    lengths.delay = json.delay;\n"
"                    if (!Object.is(cacheLengths, lengths)) {\n"
"                        lengthEl.timer.value = lengths.timer;\n"
"                        lengthEl.delay.value = lengths.delay;\n"
"                        cacheLengths = new Object(lengths);\n"
"                    }\n"
"                    color = rgbToHex(json.rgb[0], json.rgb[1], json.rgb[2]);\n"
"                    if (color != cacheColor) {\n"
"                        colorEl.value = color;\n"
"                        cacheColor = new Object(color);\n"
"                    }\n"
"                    bright = json.bright;\n"
"                    if (bright != cacheBright) {\n"
"                        brightEl.value = bright;\n"
"                        cacheBright = new Object(bright);\n"
"                    }\n"
"    \n"
"    \n"
"                });\n"
"            }, 1000);\n"
"            boolsEl.auto.onclick = function () {\n"
"                if (!buttons.auto) {\n"
"                    buttons.auto = true;\n"
"                    buttons.manual = false;\n"
"                    buttons.off = false;\n"
"                    httpGetAsync('/response?' + (new URLSearchParams(buttons).toString()), httpCallback);\n"
"                }\n"
"            };\n"
"            boolsEl.manual.onclick = function () {\n"
"                if (!buttons.manual) {\n"
"                    buttons.manual = true;\n"
"                    buttons.auto = false;\n"
"                    buttons.off = false;\n"
"                    httpGetAsync('/response?' + (new URLSearchParams(buttons).toString()), httpCallback);\n"
"                }\n"
"            };\n"
"            boolsEl.off.onclick = function () {\n"
"                if (!buttons.off) {\n"
"                    buttons.off = true;\n"
"                    buttons.auto = false;\n"
"                    buttons.manual = false;\n"
"                    httpGetAsync('/response?' + (new URLSearchParams(buttons).toString()), httpCallback);\n"
"                }\n"
"            };\n"
"            colorEl.onchange = function (event) {\n"
"                color = hexToRgb(event.target.value);\n"
"                httpGetAsync('/response?' + (new URLSearchParams({color: color}).toString()), httpCallback);\n"
"            };\n"
"            brightEl.onchange = function (event) {\n"
"                bright = event.target.value;\n"
"                httpGetAsync('/response?' + (new URLSearchParams({bright: bright}).toString()), httpCallback);\n"
"            };\n"
"            document.getElementById('tlength').onchange = function (event) {\n"
"                lengths.timer = event.target.value;\n"
"                httpGetAsync('/response?' + (new URLSearchParams(lengths).toString()), httpCallback);\n"
"            };\n"
"            document.getElementById('dlength').onchange = function (event) {\n"
"                lengths.delay = event.target.value;\n"
"                httpGetAsync('/response?' + (new URLSearchParams(lengths).toString()), httpCallback);\n"
"            };\n"
"        }\n"
"        function httpGetAsync(theUrl, callback){\n"
"            let xmlHttp = new XMLHttpRequest();\n"
"            xmlHttp.onreadystatechange = function() { \n"
"                if (xmlHttp.readyState == 4 && xmlHttp.status == 200){\n"
"                    callback(xmlHttp.responseText);\n"
"                }\n"
"            }\n"
"            xmlHttp.open('GET', theUrl, true);\n"
"            xmlHttp.send();\n"
"        }\n"
"        function httpCallback(response) {\n"
"            console.log(response);\n"
"        }\n"
"        function componentToHex(c) {\n"
"            let hex = c.toString(16);\n"
"            return hex.length == 1 ? '0' + hex : hex;\n"
"        }\n"
"        function rgbToHex(r, g, b) {\n"
"            return '#' + componentToHex(r) + componentToHex(g) + componentToHex(b);\n"
"        }\n"
"        function hexToRgb(hex) {\n"
"            let result = /^#?([a-f\\d]{2})([a-f\\d]{2})([a-f\\d]{2})$/i.exec(hex);\n"
"            return result ? [\n"
"                parseInt(result[1], 16),\n"
"                parseInt(result[2], 16),\n"
"                parseInt(result[3], 16)\n"
"            ] : null;\n"
"        }\n"
"    </script>\n"
"</body>\n"
"</html>\n";

void wifiSetup(){
  delay(10);
  Serial.println('\n');

  // wifiMulti.addAP("Netgear14", "giftedgiant916");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("Home1", "Dyadya@1966");   // add Wi-Fi networks you want to connect to
  Serial.println("Connecting ...");

  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/read", handleRead);           // Call the 'handleRead' function when a client requests URI "/response"
  server.on("/response", handleResponse);   // Call the 'handleResponse' function when a client requests URI "/response"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void wifiLoop(){
  server.handleClient();                    // Listen for HTTP requests from clients
}

void handleRoot() {
  server.send(200, "text/html", indexHtml);   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleRead() {
  dtostrf(delayLen, 6, 2, delayLenChar);
  
  String content = String("{\"auto\": ") + (autoButton ? "true" : "false") + ", \"manual\": " + (manualButton ? "true" : "false") + ", \"off\": " + (offButton ? "true" : "false") + ", \"timer\": " + timerLen + ", \"delay\": " + delayLenChar + ", \"rgb\": [" + rgb[0] + ", " + rgb[1] + ", " + rgb[2] + "]" + ", \"bright\": " + bright + "}";

  server.send(200, "application/json", content);   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleResponse() {
  if (server.hasArg("color"))
  {
    Serial.println(server.arg("color"));
    String col = server.arg("color");

    rgb[0] = getValue(col, ',', 0).toInt();
    rgb[1] = getValue(col, ',', 1).toInt();
    rgb[2] = getValue(col, ',', 2).toInt();
    settingChanged  = true;
    updateStep();
  }
  if (server.hasArg("bright"))
  {
    Serial.println(server.arg("bright"));
    bright = server.arg("bright").toInt();
    updateStep();
    settingChanged = true;
  }
  if (server.hasArg("auto"))
  {
    autoButton = server.arg("auto")[0] == 't' ? true : false;
    Serial.println(autoButton);
    if (autoButton)
    {
      resetTimer.start();
      resetTimer.reset();
      goUp = 0;
      goDown = 0;
      lastButton = 0;
      settingChanged = true;
    }
    
  }
  if (server.hasArg("manual"))
  {
    manualButton = server.arg("manual")[0] == 't' ? true : false;
    Serial.println(manualButton);

    if (manualButton)
    {
      goUp++;
      goDown++;
      resetTimer.stop();
      resetTimer.reset();
      lastButton = 1;
      settingChanged = true;
    }
  }
  if (server.hasArg("off"))
  {
    offButton = server.arg("off")[0] == 't' ? true : false;
    Serial.println(offButton);

    if (offButton)
    {
      goUp = 0;
      goDown = 0;
      lastButton = 0;
      settingChanged = true;
    }
  }
  if (server.hasArg("timer"))
  {
    timerLen = server.arg("timer").toFloat();
    Serial.println(timerLen);
    settingChanged = true;
  }
  if (server.hasArg("delay"))
  {
    delayLen = server.arg("delay").toFloat();
    Serial.println(delayLen);
    settingChanged = true;
  }
  server.send(200);
}

void handleNotFound(){
  server.send(404, "text/html", "<h1>404: Not found</h1>"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}