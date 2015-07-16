#include "hdf5.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define DATASET         "/Analyses/Basecall_2D_000/BaseCalled_2D/Fastq"

int print_fastq(char *fname);

int main(int argc, char *argv[]) 
{
  DIR *dp;
  struct dirent *ep;     

  char fullpath[1000];

    if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
	printf( "Extracts 2D Fastq from a directory of fast5 files\n");
        printf( "usage: %s dir\n", argv[0] );
	exit(0);
    }


  dp = opendir (argv[1]);

  if (dp != NULL)
  {
    char *fname;
    char *ret;

    while (ep = readdir (dp)) {
        fname = ep->d_name;
	ret = strstr(fname, ".fast5");
	/*puts (ret);*/
	if (ret != NULL) {
		strcpy(fullpath, argv[1]);
		strcat(fullpath, "/");
		strcat(fullpath, fname);
		print_fastq(fullpath);
	}
    }

    (void) closedir (dp);
  }
  else
    perror ("Couldn't open the directory");

  return 0;
}


int print_fastq(char *fname) {

    hid_t       file, filetype, memtype, dset;
                                            /* Handles */
    size_t      sdim;
    herr_t      status;
    char        *fastq;

    	    /*
	     * Open file
	     */
	    file = H5Fopen (fname, H5F_ACC_RDONLY, H5P_DEFAULT);

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
		   fastq = malloc (sdim);
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

	    }
	
	    /*
	     * Close and release resources.
	     */
	    status = H5Fclose (file);

	return 0;

}
