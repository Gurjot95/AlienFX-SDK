# AlienFX-SDK
Better AlienFX/LightFX SDK than Dell official's one without any limitations.

Dell official SDK does a very terrible job if you want to change LED color in quick succession. Their official SDK comes with 3 seconds delay and behaves pretty weird in general.
This SDK not only fixes up its issue and performs better but is written from scratch by reverse engineerig USB protocol. It sends byte data directly to USB which then changes zones color. This also removes the dependency from their Command Center software and works irrespective of settings set in stock software. In other words, you can finally achieve Rainbow effect across all LED's like it was intended without any lag. 
