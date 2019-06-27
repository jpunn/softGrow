

// Define the main elements of interest as variables, so we can access to them later in our sketch.

EmbAJAXMutableSpan Temp_display("Display1"); // a plain text displa
EmbAJAXMutableSpan Humi_display("Display2"); // a plain text displa
EmbAJAXMutableSpan Indx_display("Display3"); // a plain text displa
EmbAJAXMutableSpan Dup_display("Display4"); // a plain text displa


// Define the pages "page1"

MAKE_EmbAJAXPage(page1, "softGrow", "",
  new EmbAJAXStatic("<h1>softGrow Dashboard</h1><p>  Room Temperature:  "),
  &Temp_display,
  new EmbAJAXStatic("</p><p> Room Humidity:  "),
  &Humi_display,
 new EmbAJAXStatic("</p><p> Room Heat Index :  "),
  &Indx_display,
new EmbAJAXStatic("</p><p> Room Due Point :  "),
  &Dup_display,
  
 new EmbAJAXStatic("</p><p>Link to <a href=\"/\">page 1</a> (you can open this directly, or in a tab of your browser).</p>"),
 
)



