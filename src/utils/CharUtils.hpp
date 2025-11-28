#ifndef CHAR_HPP
#define CHAR_HPP

/**
 * @brief calculates the length of a char array
 * @param arr the char array
 * @returns the length of the char array
 */
inline int lengthOfCharArray(const char arr[])
{
    int length = 0;
    while (arr[length] != '\0')
    {
        length++;
    }
    return length;
};

/**
 * @brief converts a char to a string
 * @param c the char to convert
 * @param str the destination string
 */
inline void charToString(const char c, char str[2])
{
    str[0] = c;
    str[1] = '\0';
}

/**
 * @brief assigns a char array to another
 * @param dest the destination array
 * @param src the source array
 */
inline void charAssignment(char dest[], const char src[])
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

#endif