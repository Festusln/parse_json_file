#include<stdio.h>
#include<string.h>
#include<json-c/json.h>

int main()
{
    char buffer[1024]; //location to what is in test.json file
    FILE *fp = NULL;
    struct json_object *parsed_json;        //object struct to hold parsed json
    
    //struct to hold individual document in the json file
    struct json_object *name;
    struct json_object *id;
    struct json_object *friends;
    struct json_object *friend; //for individual element in the friends array

    size_t n_friends;   //number of element in the friends array

    fp = fopen("test.json", "r");   //opening json file in read nmode
    fread(buffer, 1024, 1, fp); //readong content into buffer
    fclose(fp); //  closing the json file

    //Parsing the json file
   parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "name", &name);
    json_object_object_get_ex(parsed_json, "id", &id);
    json_object_object_get_ex(parsed_json, "friends", &friends);

    printf("Name: %s\n", json_object_get_string(name));
    printf("id: %d\n", json_object_get_int(id));

    n_friends = json_object_array_length(friends); //getting length of array
    printf("Found %ld friends\n", n_friends);
    for (int i = 0; i<n_friends; ++i)
    {
        friend = json_object_array_get_idx(friends, i);
        printf("%d. %s\n", i+1, json_object_get_string(friend));
    }

    return 0;

}