#include <WiflyClient.h>

void setup() {
    WiflyClient client = WiflyClient(true);
    client.join_network("some_ssid", "some_password");

    client.open_connection("google.com");
    client.make_request("GET /");
    while(client.output_available()) {
        Serial.write(client.read_char_from_output());
    }
  
}


void loop() {

}
