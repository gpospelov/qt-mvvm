#include "binutils.h"


std::string file_check(std::string filename)
{
    std::ifstream mySource;
    mySource.open(filename, std::ios_base::binary);
    mySource.seekg(0, std::ios_base::end);
    int size = mySource.tellg();
    mySource.close();
    int byte_length = (size>BYTE_LENGTH)?(BYTE_LENGTH):(size);

    std::cout<<"file_size: "<<size<<std::endl;

    std::cout<<"Checking length: "<<byte_length<<std::endl;

    //checking first 1024 bytes
    int buffer[byte_length];
    std::ifstream fstr(filename, std::ios::in | std::ios::binary);

    for (int i = 0; i < byte_length; i++)
    {
        buffer[i] = fstr.get();
    }

    if(!fstr){
        std::cout<<fstr.gcount()<<std::endl;
        std::cout<<"Couldn't read from the file"<<std::endl;
        exit(1);
    }

    bool ascii = false;
    bool binary = false;

    for (size_t i = 0; i < size; i++)
    {
        if ( ( (buffer[i] >= 9) && (buffer[i] <= 13) ) ||  
            ( (buffer[i] >= 32) && (buffer[i] <= 126) ) )
        {
            ascii = true;
        }
        else
        {
            ascii = false;
            break;
        }
        
    }

    if(ascii == true)
    {
        return "Text File";
    }

    /* text file in an 8-bit
     * or variable-length ASCII-based 
     * encoding such as ISO-8859-1, 
     * UTF-8 or ASCII+Big5
    */
   for (size_t i = 0; i < size; i++)
   {
       if ( (buffer[i] >= 128) && (buffer[i] <= 255) )
       {
           ascii = true;
       }
       else
       {
           ascii = false;
           break;
       }
       
   }

   if (ascii == true)
   {
       return "Text File";
   }

   //Null check for binary files
   for (size_t i = 0; i < size; i++)
   {
       if (buffer[i] == NULL)
       {
           binary = true;
           return "Binary File";
       }
       else
       {
           binary = false;
       }  
   }

   //specially for pdf because one PDF I tested did pass the NULL test
   if ( ((char(buffer[0]) == '%') && (char(buffer[1]) == 'P')) &&
         ((char(buffer[2]) == 'D') &&(char(buffer[3]) == 'F')) )
    {
        binary = true;
        return "Binary File";
    }

   for (size_t i = 0; i < size; i++)
    {
        if ( ( (buffer[i] >= 9) && (buffer[i] <= 13) ) ||  
                ( (buffer[i] >= 32) && (buffer[i] <= 126) )||
                ( (buffer[i] >= 128) ) )
        {
            return "Text File";
        }
    }

    return "file type unknown";
}