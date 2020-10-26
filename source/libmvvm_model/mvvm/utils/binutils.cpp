#include <fstream>
#include <iostream>
#include <mvvm/utils/binutils.h>

namespace
{
//! Returns buffer size
int get_buffer_size(const std::string& filename);

//! Returns part of file content in a buffer
void get_buffer_data(const std::string& filename, int* buffer, int buffer_size);

//! Returns true if the interger is control character as defined above
bool is_control_char(int ch);

//! Returns true if there is two null bytes in the buffer
bool null_check(int* buffer, int buffer_size);
} // namespace

namespace ModelView ::Utils
{

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

    int* buffer;

    // get buffer size
    int buffer_size = get_buffer_size(filename);

    // size zero means text file
    if (buffer_size == 0) {
        return false;
    }

    // buffer allocation
    buffer = new int[buffer_size];
    get_buffer_data(filename, buffer, buffer_size);

    // control character check
    int count = 0;
    while (count < buffer_size) {
        if (is_control_char(buffer[count])) {
            return true;
        }
        count++;
    }

    // null bytes check
    if (null_check(buffer, buffer_size)) {
        return true;
    }

    return false;
}

bool is_text(const std::string& filename)
{

    return (!is_binary(filename));
}

} // namespace ModelView::Utils

namespace
{

int get_buffer_size(const std::string& filename)
{
    std::ifstream mySource;
    mySource.open(filename, std::ios_base::binary);
    mySource.seekg(0, std::ios_base::end);
    int size = mySource.tellg();
    mySource.close();
    int byte_length = (size > BYTE_LENGTH) ? (BYTE_LENGTH) : (size);

    return byte_length;
}

void get_buffer_data(const std::string& filename, int* buffer, int byte_length)
{

    std::ifstream fstr(filename, std::ios::in | std::ios::binary);

    for (int i = 0; i < byte_length; i++) {
        buffer[i] = fstr.get();
    }
}

bool is_control_char(int ch)
{
    return ((ch > NUL && ch < BS) || (ch > CR && ch < SUB));
}

bool null_check(int* buffer, int buffer_size)
{

    int count = 1;
    while (count < buffer_size) {
        // checking consecutive null chars
        if (buffer[count] == NULL_CHR && buffer[count - 1] == NULL_CHR) {
            return true;
        }
        count++;
    }

    return false;
}
} // namespace
