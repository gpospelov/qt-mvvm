#include "mvvm/utils/binutils.h"
#include <fstream>
#include <iostream>

namespace {
//! Returns buffer size
int get_buffer_size(const std::string& filename);

//! Returns part of file content in a buffer
void get_buffer_data(const std::string& filename, int* buffer, int buffer_size);

//! Returns true if the interger is control character as defined above
bool is_control_char(int ch);

//! Returns true if there is two null bytes in the buffer
bool null_check(int* buffer, int buffer_size);
} // namespace

namespace ModelView ::Utils {

// length of buffer
#define BYTE_LENGTH 2048

// null character
#define NULL_CHR (0x00)

// control characters
#define NUL 0
#define BS 8
#define CR 13
#define SUB 26

bool is_binary(const std::string& filename)
{
    int buffer[BYTE_LENGTH];

    // get buffer size
    int buffer_size = get_buffer_size(filename);
    if (buffer_size == 0)
        return false;

    // buffer allocation
    get_buffer_data(filename, buffer, buffer_size);

    // control character check
    for (int count = 0; count < buffer_size; ++count)
        if (is_control_char(buffer[count]))
            return true;

    return null_check(buffer, buffer_size);
}

bool is_text(const std::string& filename)
{

    return (!is_binary(filename));
}

} // namespace ModelView::Utils

namespace {

int get_buffer_size(const std::string& filename)
{
    std::ifstream mySource;
    mySource.open(filename, std::ios_base::binary);
    mySource.seekg(0, std::ios_base::end);
    int size = mySource.tellg();
    mySource.close();
    return (size > BYTE_LENGTH) ? BYTE_LENGTH : size;
}

void get_buffer_data(const std::string& filename, int* buffer, int byte_length)
{
    std::ifstream fstr(filename, std::ios::in | std::ios::binary);
    for (int i = 0; i < byte_length; i++)
        buffer[i] = fstr.get();
}

bool is_control_char(int ch)
{
    return ((ch > NUL && ch < BS) || (ch > CR && ch < SUB));
}

bool null_check(int* buffer, int buffer_size)
{
    for (int i = 1; i < buffer_size; ++i)
        if (buffer[i] == NULL_CHR && buffer[i - 1] == NULL_CHR)
            return true;
    return false;
}
} // namespace
