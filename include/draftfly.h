#ifndef DRAFTFLY_H
#define DRAFTFLY_H

#include <string>

namespace draftfly {
    void sendMessage(const std::string &message);
    void receiveMessages();
};

#endif