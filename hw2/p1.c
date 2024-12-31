#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Bucket{
    int cluster;
    int slot[20];
} Bucket;

typedef struct Pair{
    int bucket_pos;
    int slot_pos;
} Pair;

Bucket* hash_table[100] = {};
int bucket_num = 0;
int slot_num = 0;

int hash(int x){
    return x % bucket_num;
}

int getEmptySlot(Bucket* bucket){
    for(int i = 0; i < slot_num; i++){
        if((bucket->slot)[i] == -1) return i;
    }
    return -1;
}

bool isEmptyBucket(int bucket_pos){
    for(int i = 0; i < slot_num; i++){
        if((hash_table[bucket_pos]->slot)[i] != -1) return false;
    }
    return true;
}

void init_bucket(int bucket_pos){
    hash_table[bucket_pos] = (Bucket*)malloc(sizeof(Bucket));
    for(int i=0; i<20; i++){
        hash_table[bucket_pos]->cluster = -1;
        (hash_table[bucket_pos]->slot)[i] = -1;
    }
}

Pair search(int key){
    int bucket_pos = hash(key);
    int slot_pos = 0;
    while((hash_table[bucket_pos]->slot)[slot_pos] != key){
        slot_pos++;
        if(slot_pos >= slot_num){
            slot_pos = 0;
            bucket_pos = (bucket_pos + 1) % bucket_num;
        }
    }
    
    Pair result = { .bucket_pos = bucket_pos, .slot_pos = slot_pos};
    return result;
}

void insert(int key){
    int bucket_pos = hash(key);
    int slot_pos;
    while((slot_pos = getEmptySlot(hash_table[bucket_pos])) == -1){
        bucket_pos = (bucket_pos + 1) % bucket_num;
    }
    hash_table[bucket_pos]->cluster = hash(key);
    (hash_table[bucket_pos]->slot)[slot_pos] = key;
}

void delete(int key){
    Pair target = search(key);
    int cur_pos = target.bucket_pos;
    (hash_table[cur_pos]->slot)[target.slot_pos] = -1;
    if(isEmptyBucket(cur_pos)) hash_table[cur_pos]->cluster = -1;
}

int main(){
    for(int i=0; i<100; i++){
        init_bucket(i);
    }

    char cmd[8];
    int key;
    while(scanf("%s", cmd) != EOF){
        if(strcmp("exit", cmd) == 0){
            break;
        }
        scanf("%d", &key);
        if(strcmp("bucket", cmd) == 0){
            bucket_num = key;
        }
        else if(strcmp("slot", cmd) == 0){
            slot_num = key;
        }
        else if(strcmp("insert", cmd) == 0){
            insert(key);
        }
        else if(strcmp("delete", cmd) == 0){
            delete(key);
        }
        else if(strcmp("search", cmd) == 0){
            Pair result = search(key);
            printf("%d %d\n", result.bucket_pos, result.slot_pos);
        }
    }
}