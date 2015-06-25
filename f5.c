#include "hdf5.h"
#include <stdio.h>
#include <stdlib.h>

#define DATASET         "/Analyses/Basecall_2D_000/BaseCalled_2D/Fastq"

int main(int argc, char *argv[]) {

    hid_t       file, filetype, memtype, dset;
                                            /* Handles */
    size_t      sdim;
    herr_t      status;
    char        *fastq;
 
    if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        printf( "usage: %s filename\n", argv[0] );
	exit(0);
    }

    /*
     * Open file
     */
    file = H5Fopen (argv[1], H5F_ACC_RDONLY, H5P_DEFAULT);

    /* 
     * check it exists
     */
    status = H5Lexists(file, "/Analyses/Basecall_2D_000/BaseCalled_2D", H5P_DEFAULT);

    /*
     * if it exists, proceed
     */
    if (status == 1) {
	  /*
           * Open dataset
           */
	   dset = H5Dopen (file, DATASET, H5P_DEFAULT);

	  /*
	   * Get the datatype and its size.
	   */
	   filetype = H5Dget_type (dset);
	   sdim = H5Tget_size (filetype);
	   sdim++;                         /* Make room for null terminator */


	  /*
	   * allocate memory for the fastq string
	   */
	   fastq = (char *) malloc (sdim * sizeof (char *));

	  /*
	   * Create the memory datatype.
	   */
	   memtype = H5Tcopy (H5T_C_S1);
	   status = H5Tset_size (memtype, sdim);

	  /*
	   * Read the data.
	   */
	   status = H5Dread (dset, memtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, fastq);

	  /*
	   * Output the data to the screen.
	   */
	   printf("%s", fastq);

	   status = H5Dclose (dset);
           status = H5Tclose (filetype);
           status = H5Tclose (memtype);
	
	   free (fastq);

    } else {
           // printf ("The dataset either does NOT exist\n or some other error occurred.\n"); 
    }
	
    /*
     * Close and release resources.
     */
    status = H5Fclose (file);

}
