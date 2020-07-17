#include "binutils.h"

using namespace ModelView;

bool Utils::is_binary(std::string filename)
{

    int* buffer;

    //get buffer size
    int buffer_size = get_buffer_size(filename);

    //size zero means text file
    if (buffer_size == 0) {
        return false;
    }

    //buffer allocation
    buffer = new int[buffer_size];
    get_buffer_data(filename, buffer, buffer_size);

    //control character check
    int count = 0;
    while (count < buffer_size) {
        if (is_control_char(buffer[count])) {
            return true;
        }
        count++;
    }

    //null bytes check
    if (null_check(buffer, buffer_size)) {
        return true;
    }

    return false;
}

bool Utils::is_text(std::string filename)
{

    return (!Utils::is_binary(filename));
}

int Utils::get_buffer_size(std::string filename)
{

    std::ifstream mySource;
    mySource.open(filename, std::ios_base::binary);
    mySource.seekg(0, std::ios_base::end);
    int size = mySource.tellg();
    mySource.close();
    int byte_length = (size > BYTE_LENGTH) ? (BYTE_LENGTH) : (size);

    return byte_length;
}

void Utils::get_buffer_data(std::string filename, int* buffer, int byte_length)
{

    std::ifstream fstr(filename, std::ios::in | std::ios::binary);

    for (int i = 0; i < byte_length; i++) {
        buffer[i] = fstr.get();
    }
}

bool Utils::is_control_char(int ch)
{
    return ((ch > NUL && ch < BS) || (ch > CR && ch < SUB));
}

bool Utils::null_check(int* buffer, int buffer_size)
{

    int count = 1;
    while (count < buffer_size) {
        //checking consecutive null chars
        if (buffer[count] == NULL_CHR && buffer[count - 1] == NULL_CHR) {
            return true;
        }
        count++;
    }

    return false;
}
