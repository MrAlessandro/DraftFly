#include<iostream>
#include<draftfly.h>

int main()
{
    const std::string discoveryMessage = "Hello, I'm here!";

    // Invia un messaggio di autodiscovery
    draftfly::sendMessage(discoveryMessage);

    // Qui puoi implementare il codice per ascoltare i messaggi di risposta
    // ricevuti dagli altri dispositivi sulla rete.

    return 0;
}