#ifndef MVVM_UTILS_BINUTILS_H
#define MVVM_UTILS_BINUTILS_H

#include <fstream>
#include <iostream>


namespace ModelView
{

namespace Utils
{

//length of buffer 
#define BYTE_LENGTH 2048

//null character
#define NULL_CHR (0x00)

//control characters
#define NUL 0
#define BS 8
#define CR 13
#define SUB 26

//! Returns true if file is binary
bool is_binary(std::string filename);

//! Returns true if file is text/ascii
bool is_text(std::string filename);

//! Returns buffer size
int get_buffer_size(std::string filename);

//! Returns part of file content in a buffer
void get_buffer_data(std::string filename, int* buffer, int buffer_size);

//! Returns true if the interger is control character as defined above
bool is_control_char(int ch);

//! Returns true if there is two null bytes in the buffer
bool null_check(int* buffer, int buffer_size);

} // namespace Utils

} // namespace ModelView

#endif // MVVM_UTILS_FILEUTILS_H