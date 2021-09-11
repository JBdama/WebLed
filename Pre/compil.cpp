
#include "html_begin.pp" // header from this repo
#include "WebLed/Pre/"       // your HTML file
#include "html_end.pp"   // header from this repo

class file_provider
{
    String getHTML()
    {
        String message = html_page;
        return message;
    }
};