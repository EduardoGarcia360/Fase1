#ifndef MIAESTRUCTURAS_201212961_H
#define MIAESTRUCTURAS_201212961_H
#include <time.h>

typedef struct Sdisco Sdisco;
typedef struct Mbr Mbr;
typedef struct Particion Particion;
typedef struct EBR EBR;
typedef struct FDISK FDISK;

struct Sdisco{
    char nombre[20];
    char tamano[5];
};

struct Particion{
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
};

struct EBR{
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
};

//usado en mkdisk
struct Mbr{
    int mbr_tamano;
    time_t mbr_fecha_creacion;
    int mbr_disk_signature;
    Particion mbr_partition_1;
    Particion mbr_partition_2;
    Particion mbr_partition_3;
    Particion mbr_partition_4;
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
#endif // [MIA]ESTRUCTURAS_201212961_H
