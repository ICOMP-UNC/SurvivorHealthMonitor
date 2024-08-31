#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Step 1: Create a JSON object
    cJSON* json = cJSON_CreateObject();
    if (json == NULL)
    {
        printf("Error creating JSON object.\n");
        return 1;
    }

    // Step 2: Add a simple key-value pair
    cJSON_AddStringToObject(json, "message", "Hello, World!");
    cJSON_AddNumberToObject(json, "year", 2024);

    // Step 3: Serialize JSON object to a string
    char* jsonString = cJSON_Print(json);
    if (jsonString == NULL)
    {
        printf("Error serializing JSON object.\n");
        cJSON_Delete(json); // Clean up the JSON object
        return 1;
    }

    // Step 4: Print the JSON string
    printf("Serialized JSON:\n%s\n", jsonString);

    // Step 5: Clean up
    cJSON_Delete(json); // Free the JSON object
    free(jsonString);   // Free the JSON string

    return 0;
}
