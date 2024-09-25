#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "vector1.h"

void vector_init(Vector* this) {
	this -> size = 0;
	this -> capacity = 0;
	this -> data = NULL;
}
void vector_init_size(Vector* this, size_t n) {
	this -> size = 0;
	this -> capacity = n;
	this -> data = (int*)calloc(this -> capacity, sizeof(int));
}
void vector_init_fill(Vector* this, size_t n, int value) {
	this -> size = n;
	this -> capacity = n;
	this -> data = (int*)calloc(this -> capacity, sizeof(int));
	for (int i = 0; i < this -> size; ++i) {
		this -> data[i] = value;
	}
}
void vector_copy(Vector* this, const Vector* other) {
	if (other -> data == NULL) {
		vector_init(this);
		return;
	}
	this -> size = other -> size;
	this -> capacity = other -> capacity;
	this -> data = (int*)calloc(this -> capacity, sizeof(int));
	for (int i = 0; i < this -> size; ++i) {
		this -> data[i] = other -> data[i];
	}
}
void vector_destroy(Vector* this) {
	free(this -> data);
	this -> data = NULL;
}
Vector* vector_assign(Vector* dest, const Vector* src) {
	if (dest != src) {
		vector_destroy(dest);
		vector_copy(dest, src);
	}
	return dest;
}
int* vector_at(Vector* v, size_t index) {
	if (index > v -> size) {
		printf("out of range\n");
		return NULL;
	}
	return &(v -> data[index]);
}
int* vector_front(Vector* v) {
	if (v -> data == 0) {
		return NULL;
	}
	return &(v -> data[0]);
}
int* vector_back(Vector* v) {
	if (v -> data == 0) {
		return NULL;
	}
	return &(v -> data[v -> size]);
}
int vector_empty(const Vector* v) {
	return (v -> size == 0);
}
size_t vector_size(const Vector* v) {
	return v -> size;
}
size_t vector_capacity(const Vector* v) {
	return v -> capacity;
}
void vector_reserve(Vector* v, size_t new_cap){
	if (v -> capacity < new_cap) {
		int* new_data = (int*)calloc(new_cap, sizeof(int));
		if (new_data == NULL) {
			printf("The memory allocation is failed\n");
		}
		v -> capacity = new_cap;
		v -> data = new_data;
	 }
}
void vector_clear(Vector* v) {
	v -> size = 0;
}
void Resize_arr(Vector* v) {
		if (v -> capacity == 0) {
			v -> capacity = 1;
		}
		else {
			v -> capacity *= 2;
		}
		int* new_data = (int*)calloc(v -> capacity, sizeof(int));
		for (int i = 0; i < v -> size; ++i) {
			new_data[i] = v -> data[i];
		}
		v -> data = new_data;
}
void vector_push_back(Vector* v, int value) {
	if (v -> size < v -> capacity) {
		v -> data[v -> size] = value;
	}
	else {
		Resize_arr(v);
		v -> data[v -> size] = value;
	}
	v -> size++;
}
void vector_pop_back(Vector* v) {
	if (v -> size > 0) {
		v -> size--;
	}
}
void vector_insert(Vector* v, size_t pos, int value) {
    if (pos > v->size) {
        printf("Position out of range\n");
        return;
    }
	if (v -> size >= v -> capacity) {
		Resize_arr(v);
	}
	for (size_t i = pos; i > (v -> size) - pos; --i){
		v -> data[i] = v -> data[i - 1];
	}
	v -> data[pos] = value;
	v -> size++;
}
void vector_erase(Vector* v, size_t pos) {
	for (int i = pos; i < (v -> size) - 1; ++i) {
		v -> data[i] = v -> data[i + 1];
	}
	v -> size--;
}
void vector_resize(Vector* v, size_t count) {
	size_t new_cap;
	if (count > v -> capacity) {
		if (count > v -> capacity * 2) {
			new_cap = count;
		}
		else {
			new_cap = v -> capacity * 2;
		}
		int* new_data = (int*)calloc(new_cap, sizeof(int));
		for (int i = 0; i < v -> size; ++i) {
			new_data[i] = v -> data[i];
		}
		v -> data = new_data;
		v -> capacity = new_cap;
	}
    if (count > v->size) {
        for (size_t i = v->size; i < count; ++i) {
            v->data[i] = 0;
        }
    }
	v -> size = count;
}
void vector_swap(Vector* v1, Vector* v2) {
	int* arr = v2 -> data;
	v2 -> data = v1 -> data;
	v1 -> data = arr;

	size_t cap = v2 -> capacity;
	v2 -> capacity = v1 -> capacity;
	v1 -> capacity = cap;

	size_t xsize = v2 -> size;
	v2 -> size = v1 -> size;
	v1 -> size = xsize;
}
