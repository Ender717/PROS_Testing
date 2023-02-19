// Inclusion guard
#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

// Included libraries
#include <stdio.h>

// Included headers
#include "main.h"

/**
 * This class manages an lvgl file system driver
 * @author Nathan Sandvig
 */
class FileSystem
{
private:
    /**
     * Driver method for opening a file
     * @param file_pointer The address of the file
     * @param file_name The name of the file
     * @param mode The access mode
     * @return The result of the open operation
     */
    static lv_fs_res_t pcfs_open(void* file_pointer, const char* file_name, lv_fs_mode_t mode);

    /**
     * Driver method for closing a file
     * @param file_pointer The address of the file
     * @return The result of the close operation
     */
    static lv_fs_res_t pcfs_close(void* file_pointer);

    /**
     * Driver method for reading a file
     * @param file_pointer The address of the file
     * @param buffer The buffer to store the file data in
     * @param bytes_to_read The number of bytes to read from the file
     * @param bytes_read The storage location of the bytes which are read
     * @return The result of the read operation
     */
    static lv_fs_res_t pcfs_read(void* file_pointer, void* buffer, uint32_t bytes_to_read, uint32_t* bytes_read);

    /**
     * Driver method for seeking a location in a file
     * @param file_pointer The address of the file
     * @param position The position to seek in that file
     * @return The result of the seek operation
     */
    static lv_fs_res_t pcfs_seek(void* file_pointer, uint32_t position);

    /**
     * Driver method for telling the position of a file
     * @param file_pointer The address of the file
     * @param position_pointer The storage location of the position which is read
     * @return The result of the tell operation
     */
    static lv_fs_res_t pcfs_tell(void* file_pointer, uint32_t* position_pointer);

public:
    /**
     * Initializes the pcfs filesystem driver
     */
    static void pcfs_initialize();
};

#endif