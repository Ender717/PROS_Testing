// Included header
#include "menu/FileSystem.h"

lv_fs_res_t FileSystem::pcfs_open(void* file_pointer, const char* file_name, lv_fs_mode_t mode)
{
    // Sets the access mode flags
    errno = 0;
    const char * flags = "";
    if(mode == LV_FS_MODE_WR)
        flags = "wb";
    else if(mode == LV_FS_MODE_RD)
        flags = "rb";
    else if(mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
        flags = "a+";

    // Opens the file
    char buf[256];
    sprintf(buf, "/%s", file_name);
    FILE* f = fopen(buf, flags);

    // Confirms file opening and sets seek location to 0
    if(f == NULL)
      return LV_FS_RES_UNKNOWN;
    else
    {
      fseek(f, 0, SEEK_SET);
      FILE** fp = (FILE**)file_pointer;
      *fp = f;
    }

    return LV_FS_RES_OK;
}

lv_fs_res_t FileSystem::pcfs_close(void* file_pointer)
{
    FILE** fp = (FILE**)file_pointer;
    fclose(*fp);
    return LV_FS_RES_OK;
}

lv_fs_res_t FileSystem::pcfs_read(void* file_pointer, void* buffer, uint32_t bytes_to_read, uint32_t* bytes_read)
{
    FILE** fp =  (FILE**)file_pointer;
    *bytes_read = fread(buffer, 1, bytes_to_read, *fp);
    return LV_FS_RES_OK;
}

lv_fs_res_t FileSystem::pcfs_seek(void* file_pointer, uint32_t position)
{
    FILE** fp = (FILE**)file_pointer;
    fseek(*fp, position, SEEK_SET);
    return LV_FS_RES_OK;
}

lv_fs_res_t FileSystem::pcfs_tell(void* file_pointer, uint32_t* position_pointer)
{
    FILE** fp =  (FILE**)file_pointer;
    *position_pointer = ftell(*fp);
    return LV_FS_RES_OK;
}

void FileSystem::pcfs_initialize()
{
    // Initialize the driver in memory
    lv_fs_drv_t pcfs_drv;
    memset(&pcfs_drv, 0, sizeof(lv_fs_drv_t));

    // Sets the fields of the driver
    pcfs_drv.file_size = sizeof(FILE*);
    pcfs_drv.letter = 'S';
    pcfs_drv.open = pcfs_open;
    pcfs_drv.close = pcfs_close;
    pcfs_drv.read = pcfs_read;
    pcfs_drv.seek = pcfs_seek;
    pcfs_drv.tell = pcfs_tell;

    // Adds the driver to the lvgl file system
    lv_fs_add_drv(&pcfs_drv);
}