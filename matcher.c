/**
 Evan Carlson
 20463800 
*/

#include "matcher.h"

/**
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
    if (*partial_line == *pattern || *pattern == '\0') {
        return 1;
    }
    return 0;
}

/**
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */
int rgrep_matches(char *line, char *pattern) {
    char pattern_char = *pattern;
    if (pattern_char == '\0') {
        return 1; // reached end of string through recursion
    }
    // CHECK FOR '/' TO POTENTIALLY NULLIFY NEXT CHAR
    if (pattern_char == '\\') {
        if (*(pattern + 2) == '?') { // check pattern for nullified special char followed by +
            if (matches_leading(line, pattern + 3) && !matches_leading(line + 1, pattern + 3)) {
                return rgrep_matches(line, pattern + 3);
            }
	    else if (*line == *(pattern + 1)) {
                return rgrep_matches(line + 1, pattern + 3);
            }
	    else {
                return rgrep_matches(line, pattern + 3);
            }
        }
	else if (matches_leading(line, pattern + 1)) { // if next char and pattern_char match
            return rgrep_matches(line + 1, pattern + 2);
        }
	else { // if they don't
            return 0;
        }
    }
    
    // CHECK NEXT CHAR FOR '+'
    else if (*(pattern + 1) == '+') { // char must occur one or more times
        if ((*line == pattern_char) || (pattern_char == '.' && *line != '\0')) { // test case: ...+\.
            if (*(pattern + 2) == '\\' && matches_leading(line + 1, pattern + 3)) { // if next char (not +) is '\', check if next next pattern is next char
                return rgrep_matches(line + 1, pattern + 2);
            }
	    else if (*(pattern + 2) == '.' || matches_leading(line + 1, pattern + 2)) { // test case: .+.
                return rgrep_matches(line + 1, pattern + 2);
            }
	    else { // if next char and next char (not +) match
                return rgrep_matches(line + 1, pattern);
            }
        }
	else { // no valid match
            return 0;
        }
    }

    // CHECK NEXT CHAR FOR '?'
    else if (*(pattern + 1) == '?') { // if '?', current character is optional
        if (matches_leading(line, pattern + 2) && !matches_leading(line + 1, pattern + 2)) {
            return rgrep_matches(line, pattern + 2);
        }
	else if (*line == pattern_char) {
            return rgrep_matches(line + 1, pattern + 2);
        }
	else { // if they don't match
            return rgrep_matches(line, pattern + 2);
        }
    }

    // CHECK FOR MATCH
    else if ((*line == pattern_char) || (pattern_char == '.' && *line != '\0')) { // match
        return rgrep_matches(line + 1, pattern + 1); // move on to next line char AND pattern char
    }
    else {
        return 0; // no match
    }
}
