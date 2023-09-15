# task 7 read_matrix
int* read_matrix(char* filename, int* row, int* col){
	File* file = fopen(filename, "rb");
	if(file == null){
		fopen_error();
	}

	fread(row, size_4, 1, file);
	fread(col, size_4, 1, file);	

	int* matrix = (int *)malloc((*row) * (*col) * size_4);
	if(matrix == 0){
		matrix_error;
	}
	int byte_read = fread(matrix, size_4, (*row) * (*col), file);
	if(byte_read != (*row) * (*col)){
		free(matrix);
		fclose(file);
		fread_error;
	}
	if(fclose(file) == -1){
		fclose_error;
	}
	return matrix;
}

void write_matrix(char* filename, int*matrix, int rows, int cols){
	File* file = fopen(filename,"wb");
	if(file == null){
		fopen_error;
	}
	fwrite(&rows,size_4,1,file);
	fwrite(&cols,size_4,1,file);

	fwrite(matrix,size_4,rows*cols,file);

	if(fclose(file) == -1){
		fclose_error;
	}

}

int classify(int argc, char** argv,int a2){
	int num_rows_m0,num_cols_m0;
	int num_rows_m1,num_cols_m1;
	int num_rows_input,num_cols_input;
	int* m0, m1, input;

	m0 = read_matrix(argv[1],&num_rows_m0,&num_rows_m0);
	m1 = read_matrix(argv[2],&num_rows_m1,&num_rows_m1);
	input = read_matrix(argv[3],&num_rows_input,&num_rows_input);

	int* h;
	matmul(m0,input,h)
	relu(h,h_size(num_rows_m0*num_cols_input));

	int* o;
	matmul(m1,h,o);
	write_matrix(argv[4],o,num_rows_m1,num_cols_input);

	int classification = argmax(o,o_size);
	if(a2 == 0){
		print_int(classification);
        print_char('\n');
	}
	free(o);
	free(h);
	free(m0);
	free(m1);
	free(input);
	free(num_rows_m0);
	...
	free(num_cols_input);

	return classification;
}