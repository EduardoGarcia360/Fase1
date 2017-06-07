#ifndef MIAESTRUCTURAS_201212961_H
#define MIAESTRUCTURAS_201212961_H
#include <time.h>

typedef struct Sdisco Sdisco;
typedef struct Mbr Mbr;
typedef struct Particion Particion;

struct Sdisco{
    char nombre[50];
    char tamano[5];
    char particiones[9];
    char puntero[9];
};

struct Particion{
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name;
};

struct Mbr{
    int mbr_tamano;
    time_t mbr_fecha_creacion;
    int mbr_disk_signature;
    Particion mbr_partition_1;
    Particion mbr_partition_2;
    Particion mbr_partition_3;
    Particion mbr_partition_4;
};

#endif // [MIA]ESTRUCTURAS_201212961_H
