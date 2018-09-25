# WiflyRequests

I was extremely frustrated with the state of the WiFly library. As far as I can tell, very little of it actually works.
My WiFly worked, and I was just trying to make a simple request to a server, yet everything kept failing with the
existing library. I tried to figure out why, but eventually gave up. Instead, I began sending serial commands directly
to the module, and that actually did work. So I built a library that uses some of the WiFly library (mostly the low-level
parts that actually work) and abstracts away the annoying serial stuff (though it also makes it easy to send serial commands if necessary). I only wrote WiflyClient.h and WiflyClient.cpp, the rest is from the existing library.


### Usage

First, you setup a client with

```
WiflyClient client = WiflyClient(debug);
```

where debug is a bool. If debug is true, then the code will send all of its output pre-request to Serial at 9600.
Otherwise, there won't be any Serial output, and only the final request data will actually be returned.


Second, you have to get the WiFly to join a network:
```
client.join_network("some_network_ssid", "some_network_password")
```
If you just pass the ssid, then the network is assumed to be open.


Third, you need to open a connection to wherever it is you want to make a request:
```
client.open_connection("some_domain.com")
```

Fourth, make a request:
```
client.make_request("GET /some_page?with=some&parameters=set")
```

Finally, iterate through the response to the request:
```
while(client.output_available()) {
   char read_char = client.read_char_from_output();
   // do something with read_char
}
```
There is also an example in the examples directory.


### Some Sketchiness

There are a couple of sketch things you should be aware of in this library:
1) If you have debug on, you'll probably see "ERR: ?-Cmd" at least twice. This actually isn't a problem. If you want
you can look at the comments in WiflyClient.cpp, but basically don't worry about it.
2) If you get an error with debug on that says "ERR: BAD ADDRESS", that probably means the network couldn't be joined.
Look further up in the output and you'll probably see the network wasn't joined. The address is just an effect that
happens later and it doesn't actually mean the url is bad (if your url is actually bad, you'll also get this error, but
not a network error).

### A Suggestion
I would HIGHLY recommend not actually trying to get the contents of a webpage designed for humans. First,
the data will come in very slowly (fifteen seconds to load google? Probably.). Second, it's basically impossible to
scrape anything in C++ without the standard library, so I'm not sure what you'd even do with that. Instead, set up a
server somewhere that gets the webpage of interest and processes it down to the absolute bare minimum, and then get from
the server.

### For anyone who finds this useful
I like bars of plain milk chocolate.

### In case you are also using my arduino
Yes I know, I soldered the shield backwards, crooked, and also in a place I didn't need to. It was my first time
soldering, ok?
