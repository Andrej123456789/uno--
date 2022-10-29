/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: Apache License 2.0
 * DESCRIPTION: util.c, C file for helper functions
*/

#include "include/util.h"

/**
 * Copying settings from JSON file to the struct
 * @param settings - struct where to copy most of settings 
 * @param points - struct where is `match_point` variable going
 * @param path - path of the file, length is 40 
*/
int copy_json(Settings* settings, Points* points, char* path)
{
    FILE* file;
    file = fopen(path, "r");

    if (file == NULL)
    {
        printf("File not found!\n");
        return 1;
    }

    char buffer[1024];

    struct json_object* parsed_json;
    struct json_object* j_match_points;
    struct json_object* j_players;
    struct json_object* j_special_mode;
    struct json_object* j_debug_mode;
    struct json_object* j_swap_card;
    struct json_object* j_colors;
    struct json_object* j_ai_sequence;
    struct json_object* j_network_sequence;

    int match_points, players, special_mode, debug_mode, swap_card, colors;

    fread(buffer, 1024, 1, file);
    fclose(file);

    /* Settings which are not sequences */
    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "match_points", &j_match_points);
    json_object_object_get_ex(parsed_json, "players", &j_players);
    json_object_object_get_ex(parsed_json, "special_mode", &j_special_mode);
    json_object_object_get_ex(parsed_json, "debug_mode", &j_debug_mode);
    json_object_object_get_ex(parsed_json, "swap_card", &j_swap_card);
    json_object_object_get_ex(parsed_json, "colors", &j_colors);

    match_points = json_object_get_int(j_match_points);
    players = json_object_get_int(j_players);
    special_mode = json_object_get_int(j_special_mode);
    debug_mode = json_object_get_int(j_debug_mode);
    swap_card = json_object_get_int(j_swap_card);
    colors = json_object_get_int(j_colors);

    points->match_points = match_points;
    settings->players = players;
    settings->special_mode = special_mode;
    settings->debug_mode = debug_mode;
    settings->swap_card = swap_card;
    settings->colors = colors;

    /* Sequences */
    json_object_object_get_ex(parsed_json, "ai_sequence", &j_ai_sequence);
    json_object_object_get_ex(parsed_json, "network_sequence", &j_network_sequence);

    strcpy(settings->json_ai_sequence, json_object_get_string(j_ai_sequence));
    strcpy(settings->json_network_sequence, json_object_get_string(j_network_sequence));

    /* Print settings */
    printf("Your current settings are:\n");
    printf("\t Players: %d\n", settings->players);
    printf("\t Special Mode: %d\n", settings->special_mode);
    printf("\t Debug Mode: %d\n", settings->debug_mode);
    printf("\t Swap Card: %d\n", settings->swap_card);
    printf("\t Colors: %d\n", settings->colors);
    printf("\t AI sequence: %s\n", settings->json_ai_sequence);
    printf("\t Network sequence: %s\n", settings->json_network_sequence);
    printf("\n");

    return 0;
}

/**
 * Replacing line in the file.
 * Credits: https://codeforwin.org/2018/02/c-program-replace-specific-line-a-text-file.html
 * @param path - the path to the file
 * @param line - the line number
 * @param text_size - size of new text
 * @param text - the new text
*/
void replace_line(const char* path, int line, int text_size, char new_text[text_size])
{
    int count;
    char buffer[1000];

    /* Open all required files */
    FILE* fPtr = fopen(path, "r");
    FILE* fTemp = fopen("replace.tmp", "w");

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(0);
    }

    /*
     * Read line from source file and write to destination 
     * file after replacing given line.
    */
    count = 0;
    while ((fgets(buffer, text_size, fPtr)))
    {
        count++;

        /* If current line is line to replace */
        if (count == line)
        {
            fputs(new_text, fTemp);
        }

        else
        {
            fputs(buffer, fTemp);
        }
    }

    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

    /* Delete original source file */
    remove(path);

    /* Rename temporary file as original file */
    rename("replace.tmp", path);
}
