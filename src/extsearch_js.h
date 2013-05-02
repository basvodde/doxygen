"function SearchBox(name, resultsPath, inFrame, label)\n"
"{\n"
"  this.searchLabel = label;\n"
"  this.DOMSearchField = function()\n"
"  {  return document.getElementById(\"MSearchField\");  }\n"
"  this.DOMSearchBox = function()\n"
"  {  return document.getElementById(\"MSearchBox\");  }\n"
"  this.OnSearchFieldFocus = function(isActive)\n"
"  {\n"
"    if (isActive)\n"
"    {\n"
"      this.DOMSearchBox().className = 'MSearchBoxActive';\n"
"      var searchField = this.DOMSearchField();\n"
"      if (searchField.value == this.searchLabel) \n"
"      {\n"
"        searchField.value = '';\n"
"      }\n"
"    }\n"
"    else\n"
"    {\n"
"      this.DOMSearchBox().className = 'MSearchBoxInactive';\n"
"      this.DOMSearchField().value   = this.searchLabel;\n"
"    }\n"
"  }\n"
"}\n"
"\n"
"function trim(s) {\n"
"  return s?s.replace(/^\\s\\s*/, '').replace(/\\s\\s*$/, ''):'';\n"
"}\n"
"\n"
"function getURLParameter(name) {\n"
"  return decodeURIComponent((new RegExp('[?|&]'+name+\n"
"         '='+'([^&;]+?)(&|#|;|$)').exec(location.search)\n"
"         ||[,\"\"])[1].replace(/\\+/g, '%20'))||null;\n"
"}\n"
"\n"
"var entityMap = {\n"
"  \"&\": \"&amp;\",\n"
"  \"<\": \"&lt;\",\n"
"  \">\": \"&gt;\",\n"
"  '\"': '&quot;',\n"
"  \"'\": '&#39;',\n"
"  \"/\": '&#x2F;'\n"
"};\n"
"\n"
"function escapeHtml(s) {\n"
"  return String(s).replace(/[&<>\"'\\/]/g, function (s) {\n"
"    return entityMap[s];\n"
"  });\n"
"}\n"
"\n"
"function searchFor(query,page,count) {\n"
"  $.getJSON(serverUrl+\"?cb=?\",\n"
"  {\n"
"    n:count,\n"
"    p:page,\n"
"    q:query\n"
"  },\n"
"  function(data) {\n"
"    var results = $('#searchresults');\n"
"    $('#MSearchField').val(query);\n"
"    if (data.hits>0) {\n"
"      if (data.hits==1) {\n"
"        results.html('<p>'+searchResultsText[1]+'</p>');\n"
"      } else {\n"
"        results.html('<p>'+searchResultsText[2].replace(/\\$num/,data.hits)+'</p>');\n"
"      }\n"
"      var r='<table>';\n"
"      $.each(data.items, function(i,item){\n"
"        var prefix = tagMap[item.tag];\n"
"        if (prefix) prefix+='/'; else prefix='';\n"
"        r+='<tr class=\"searchresult\">'+\n"
"           '<td align=\"right\">'+(data.first+i+1)+'.</td>'+\n"
"           '<td>'+escapeHtml(item.type)+'&#160;'+\n"
"                '<a href=\"'+escapeHtml(prefix+item.url)+\n"
"                '\">'+escapeHtml(item.name)+'</a>';\n"
"        if (item.type==\"source\") {\n"
"          var l=item.url.match(/[1-9][0-9]*$/);\n"
"          if (l) r+=' at line '+parseInt(l[0]);\n"
"        }\n"
"        r+='</td>';\n"
"        for (var i=0;i<item.fragments.length;i++)\n"
"        {\n"
"          r+='<tr><td></td><td>'+item.fragments[i]+'</td></tr>';\n"
"        }\n"
"        r+='</tr>';\n"
"      });\n"
"      r+='</table>';\n"
"      if (data.pages>1) // write multi page navigation bar\n"
"      {\n"
"        r+='<div class=\"searchpages\">';\n"
"        if (data.page>0)\n"
"        {\n"
"          r+='<span class=\"pages\"><a href=\"javascript:searchFor(\\''+escapeHtml(query)+'\\','+(page-1).toString()+','+count.toString()+')\">&laquo;</a></span>&nbsp;';\n"
"        }\n"
"        var firstPage = data.page-5;\n"
"        var lastPage  = data.page+5;\n"
"        if (firstPage<0)\n"
"        {\n"
"          lastPage-=firstPage;\n"
"          firstPage=0;\n"
"        }  \n"
"        if (lastPage>data.pages)\n"
"        {\n"
"          lastPage=data.pages;\n"
"        }\n"
"        for(var i=firstPage;i<lastPage;i++)\n"
"        {\n"
"          if (i==data.page)\n"
"          {\n"
"            r+='<span class=\"pages\"><b>'+(i+1).toString()+'</b></span>&nbsp;';\n"
"          }\n"
"          else\n"
"          {\n"
"            r+='<span class=\"pages\"><a href=\"javascript:searchFor(\\''+escapeHtml(query)+'\\','+i.toString()+','+count.toString()+')\">'+(i+1).toString()+'</a></span>&nbsp;';\n"
"          }\n"
"        }\n"
"        if (data.page+1<data.pages)\n"
"        {\n"
"          r+='<span class=\"pages\"><a href=\"javascript:searchFor(\\''+escapeHtml(query)+'\\','+(page+1).toString()+','+count.toString()+')\">&raquo;</a></span>';\n"
"        }\n"
"        r+='</div>';\n"
"      }\n"
"      results.append(r);\n"
"    } else {\n"
"      results.html('<p>'+searchResultsText[0]+'</p>');\n"
"    }\n"
"  });\n"
"}\n"
