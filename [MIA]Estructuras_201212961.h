#ifndef MIAESTRUCTURAS_201212961_H
#define MIAESTRUCTURAS_201212961_H
#include <time.h>

typedef struct Mbr Mbr;
typedef struct Particion Particion;
typedef struct EBR EBR;
typedef struct Lista_EBR Lista_EBR;
typedef struct FDISK FDISK;

struct Particion{
    char part_status;
    char part_type;
    char part_fit[2];
    int part_start;
    int part_size;
    char part_name[16];
};

struct EBR{
    char part_status;
    int part_next;
    char part_fit[2];
    int part_start;
    int part_size;
    char part_name[16];
    EBR* siguiente;
};

struct Lista_EBR{
    EBR* inicio;
};

//usado en mkdisk
struct Mbr{
    int mbr_tamano;
    time_t mbr_fecha_creacion;
    int mbr_disk_signature;
    //para primarias y extendidas
    Particion mbr_partition_1;
    Particion mbr_partition_2;
    Particion mbr_partition_3;
    Particion mbr_partition_4;
    //para logicas dentro de extendidas
    EBR ebr_particion_1;
    EBR ebr_particion_2;
    EBR ebr_particion_3;
    EBR ebr_particion_4;
};

struct FDISK{
        //obligatorios
    int SIZE;
    char PATH[100];
    char NAME[30];
        //opcionales
    char UNIT;
    char TYPE;
    char FIT[2];//(para dos o mas se utiliza array)
    char _DELETE;
    int ADD;
    int MOV; //aun no se que es
};

void agregarParticionEX(Lista_EBR* lalista, char status, char fit, int start, int size, int next, char name[16]);
#endif // [MIA]ESTRUCTURAS_201212961_H
