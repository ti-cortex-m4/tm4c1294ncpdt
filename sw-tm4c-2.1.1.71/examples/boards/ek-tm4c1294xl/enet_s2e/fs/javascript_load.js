<!-- Copyright (c) 2014-2015 Texas Instruments Incorporated.  All rights reserved. -->

window.onload = function()
{
    document.getElementById('about').onclick = loadAbout;
    document.getElementById('overview').onclick = loadOverview;
    document.getElementById('block').onclick = loadBlock;
    document.getElementById('config1').onclick = loadConfig1;
    document.getElementById('config2').onclick = loadConfig2;
    document.getElementById('misc').onclick = loadMisc;
    document.getElementById('upd').onclick = loadUpd;

    loadPage("about.htm");
}
