typedef struct {
    char magic_number[3]; 
    int width;           
    int height;          
    int max_value;       
    int **pixels;        
} PNM;


int load_pnm(PNM **image , char* filename);


int write_pnm(PNM *image , char* filename);

void free_pnm(PNM *image);