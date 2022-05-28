#include "Errors.h"

const std::string& POSError::getMessage()const noexcept{
    return message;
}