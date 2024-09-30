#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>



/* Creating structure for sensors with data to be measured. */

typedef struct {
    int bpm; // Beats per minute (heart rate)
} HeartRate;

typedef struct {
    float celsius; // Temperature in Celsius
} Temperature;

typedef struct {
    float percentage; // Oxygen saturation percentage
} OxygenSaturation;

// Function to serialize a HeartRate structure into a JSON object
cJSON* serialize_heart_rate(HeartRate hr) {
    cJSON* json = cJSON_CreateObject();
    if (json == NULL) {
        return NULL; // Return NULL if the JSON object couldn't be created
    }
    cJSON_AddNumberToObject(json, "bpm", hr.bpm); // Add the bpm value to the JSON object
    return json; // Return the created JSON object
}

// Function to serialize a Temperature structure into a JSON object
cJSON* serialize_temperature(Temperature temp) {
    cJSON* json = cJSON_CreateObject();
    if (json == NULL) {
        return NULL; // Return NULL if the JSON object couldn't be created
    }
    cJSON_AddNumberToObject(json, "celsius", temp.celsius); // Add the celsius value to the JSON object
    return json; // Return the created JSON object
}

// Function to serialize an OxygenSaturation structure into a JSON object
cJSON* serialize_oxygen_saturation(OxygenSaturation os) {
    cJSON* json = cJSON_CreateObject();
    if (json == NULL) {
        return NULL; // Return NULL if the JSON object couldn't be created
    }
    cJSON_AddNumberToObject(json, "percentage", os.percentage); // Add the percentage value to the JSON object
    return json; // Return the created JSON object
}

// Function to deserialize a JSON object into a HeartRate structure
HeartRate deserialize_heart_rate(cJSON* json) {
    HeartRate hr;
    cJSON* bpm = cJSON_GetObjectItem(json, "bpm"); // Get the bpm value from the JSON object
    if (cJSON_IsNumber(bpm)) {
        hr.bpm = bpm->valueint; // Assign the bpm value to the HeartRate structure if it's a number
    }
    return hr; // Return the deserialized HeartRate structure
}

// Function to deserialize a JSON object into a Temperature structure
Temperature deserialize_temperature(cJSON* json) {
    Temperature temp;
    cJSON* celsius = cJSON_GetObjectItem(json, "celsius"); // Get the celsius value from the JSON object
    if (cJSON_IsNumber(celsius)) {
        temp.celsius = celsius->valuedouble; // Assign the celsius value to the Temperature structure if it's a number
    }
    return temp; // Return the deserialized Temperature structure
}

// Function to deserialize a JSON object into an OxygenSaturation structure
OxygenSaturation deserialize_oxygen_saturation(cJSON* json) {
    OxygenSaturation os;
    cJSON* percentage = cJSON_GetObjectItem(json, "percentage"); // Get the percentage value from the JSON object
    if (cJSON_IsNumber(percentage)) {
        os.percentage = percentage->valuedouble; // Assign the percentage value to the OxygenSaturation structure if it's a number
    }
    return os; // Return the deserialized OxygenSaturation structure
}

int main() {
    // Example sensor data
    HeartRate hr = {75};
    Temperature temp = {36.5};
    OxygenSaturation os = {98.0};

    // Serialization
    cJSON* json_hr = serialize_heart_rate(hr);
    cJSON* json_temp = serialize_temperature(temp);
    cJSON* json_os = serialize_oxygen_saturation(os);

    // Convert JSON objects to strings
    char* jsonString_hr = cJSON_Print(json_hr);
    char* jsonString_temp = cJSON_Print(json_temp);
    char* jsonString_os = cJSON_Print(json_os);

    printf("Heart Rate JSON:\n%s\n", jsonString_hr);
    printf("Temperature JSON:\n%s\n", jsonString_temp);
    printf("Oxygen Saturation JSON:\n%s\n", jsonString_os);

    // Deserialization
    HeartRate hr_deserialized = deserialize_heart_rate(json_hr);
    Temperature temp_deserialized = deserialize_temperature(json_temp);
    OxygenSaturation os_deserialized = deserialize_oxygen_saturation(json_os);

    printf("Deserialized Heart Rate: %d bpm\n", hr_deserialized.bpm);
    printf("Deserialized Temperature: %.1f°C\n", temp_deserialized.celsius);
    printf("Deserialized Oxygen Saturation: %.1f%%\n", os_deserialized.percentage);

    // Clean up memory
    cJSON_Delete(json_hr);
    cJSON_Delete(json_temp);
    cJSON_Delete(json_os);
    free(jsonString_hr);
    free(jsonString_temp);
    free(jsonString_os);

    return 0;
}
