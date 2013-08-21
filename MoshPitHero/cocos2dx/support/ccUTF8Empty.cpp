/*
*
*   This file is an empty implementation of the ccUTF8 functions to workaround the use of code from GLIB.
*   The current project does not require this functionality so this will suffice for the time being
 */

#include "ccUTF8.h"

NS_CC_BEGIN

int cc_wcslen(const unsigned short* str)
{
    return 0;
}


/*
 * @str:    the string to search through.
 * @c:        the character to not look for.
 *
 * Return value: the index of the last character that is not c.
 * */
unsigned int cc_utf8_find_last_not_char(std::vector<unsigned short> str, unsigned short c)
{
    return 0;
}

/*
 * @str:    the string to trim
 * @index:    the index to start trimming from.
 *
 * Trims str st str=[0, index) after the operation.
 *
 * Return value: the trimmed string.
 * */
static void cc_utf8_trim_from(std::vector<unsigned short>* str, int index)
{

}

/*
 * @ch is the unicode character whitespace?
 *
 * Reference: http://en.wikipedia.org/wiki/Whitespace_character#Unicode
 *
 * Return value: weather the character is a whitespace character.
 * */
bool isspace_unicode(unsigned short ch)
{
    return false;
}

void cc_utf8_trim_ws(std::vector<unsigned short>* str)
{

}

/*
 * cc_utf8_strlen:
 * @p: pointer to the start of a UTF-8 encoded string.
 * @max: the maximum number of bytes to examine. If @max
 *       is less than 0, then the string is assumed to be
 *       null-terminated. If @max is 0, @p will not be examined and
 *       may be %NULL.
 *
 * Returns the length of the string in characters.
 *
 * Return value: the length of the string in characters
 **/
long
cc_utf8_strlen (const char * p, int max)
{
    return 0;
}

/*
 * g_utf8_get_char:
 * @p: a pointer to Unicode character encoded as UTF-8
 *
 * Converts a sequence of bytes encoded as UTF-8 to a Unicode character.
 * If @p does not point to a valid UTF-8 encoded character, results are
 * undefined. If you are not sure that the bytes are complete
 * valid Unicode characters, you should use g_utf8_get_char_validated()
 * instead.
 *
 * Return value: the resulting character
 **/
static unsigned int
cc_utf8_get_char (const char * p)
{
    return 0;
}


unsigned short* cc_utf8_to_utf16(const char* str_old, int length/* = -1 */, int* rUtf16Size/* = NULL */)
{
    return 0;
}

std::vector<unsigned short> cc_utf16_vec_from_utf16_str(const unsigned short* str)
{
    std::vector<unsigned short> str_new;
    return str_new;
}

/**
 * cc_unichar_to_utf8:
 * @c: a ISO10646 character code
 * @outbuf: output buffer, must have at least 6 bytes of space.
 *       If %NULL, the length will be computed and returned
 *       and nothing will be written to @outbuf.
 *
 * Converts a single character to UTF-8.
 *
 * Return value: number of bytes written
 **/
int
cc_unichar_to_utf8 (unsigned short c,
                   char   *outbuf)
{
    return 0;
}


/**
 * cc_utf16_to_utf8:
 * @str: a UTF-16 encoded string
 * @len: the maximum length of @str to use. If @len < 0, then
 *       the string is terminated with a 0 character.
 * @items_read: location to store number of words read, or %NULL.
 *              If %NULL, then %G_CONVERT_ERROR_PARTIAL_INPUT will be
 *              returned in case @str contains a trailing partial
 *              character. If an error occurs then the index of the
 *              invalid input is stored here.
 * @items_written: location to store number of bytes written, or %NULL.
 *                 The value stored here does not include the trailing
 *                 0 byte.
 * @error: location to store the error occuring, or %NULL to ignore
 *         errors. Any of the errors in #GConvertError other than
 *         %G_CONVERT_ERROR_NO_CONVERSION may occur.
 *
 * Convert a string from UTF-16 to UTF-8. The result will be
 * terminated with a 0 byte.
 *
 * Return value: a pointer to a newly allocated UTF-8 string.
 *               This value must be freed with free(). If an
 *               error occurs, %NULL will be returned and
 *               @error set.
 **/
char *
cc_utf16_to_utf8 (const unsigned short  *str,
                 long             len,
                 long            *items_read,
                 long            *items_written)
{
   return NULL;
}

NS_CC_END
