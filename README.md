# Help-Me

A script that once the a button is pressed the board will send a text message.

To use this script, you must fill out the SSID, wifi password and maker key point.

This was done using IFTTT (https://ifttt.com/) to send a message to me on Slack once an event, from the ESP board, is triggered. So in order to fill out the makerkey, you must also create a service that replicates the same thing.

From IFTT, download the Maker Webhooks and Slack applets, after doing that click create and 
make the *this* point to webhooks

- create an event to trigger, I named my event "ESP". If you do name it something different you must to change the url on line 58 of main.cpp code.


then make the *that* point to Slack

- This is fairly straight forward, just connect your slack.


After hooking up the IFTTT, get the maker key which can be found in https://ifttt.com/maker_webhooks/settings and fill it in the parameters.

Then upload the code to your board and viola!
