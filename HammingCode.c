#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include <ctype.h>  

#define SIZE_OF_ARRAY 20
static char input_datastream[SIZE_OF_ARRAY];
int* assign_array(int bits_length, int change_bits, int assigned_data_stream);
int hamming(int* data_stream, int* data_stream_error, int bits_length);
int calculate_databit(int bit_position);
unsigned int get_bit_position(unsigned int binary);

void main()
{
    int rerun = 0;
     do{
        int bits_length = 0, validation ,input_bit_position;
        char input_rerun;
        do{
            validation = 0;
            printf("\nLength of Bits: ");         //Input the length of bits
            scanf("%d", &bits_length);         //Get the number of requires_bits
            (bits_length == 8 || bits_length == 16)? validation = 1: printf("Please input '8' or '16'...\n\n"); //Validation for the right bits
        }while(validation == 0);

        //Check if length of bits is correct before computing the data stream
        do{
            validation = 0;
            printf("The data stream without error: ");
            scanf("%s", &input_datastream);

            if(strlen(input_datastream) == bits_length)
            {
                validation = 1;
                for(int i = 0; i < bits_length; i++)
                { 
                    (input_datastream[i] == '0' ||input_datastream[i] == '1' )? validation : validation--;
                    if(!validation) //Print only if value is not 1 and 0
                    {
                        i = bits_length;
                        printf("Please input '1' or '0'...\n\n");
                    }      
                }
            }
            else
            {
                printf("Please input the correct length...\n\n");
            }
        }while(validation == 0);

        do
        {
            validation = 0;
            printf("Which data bit has error occur:");
            scanf("%d", &input_bit_position);
            
            (input_bit_position > bits_length || input_bit_position ==0) ? (bits_length == 8) ? printf("Please keep within the range of 1 - 8...\n") : 
            + printf("Please keep within the range of 1 - 16...\n") : validation++;  //Check if length is within the bit_length; Differnt lenght different output
        } while (validation == 0);

        int* data_stream = assign_array(bits_length, input_bit_position - 1, 0); //Assign to new array for data stream without error
        int* data_stream_error = assign_array(bits_length, input_bit_position - 1, 1);  //Assign to new array for data stream with error

        int sydrome_word = hamming(data_stream, data_stream_error, bits_length);
        int bits_position = 0;
        while(get_bit_position(bits_position) != sydrome_word) //Issues here sydrome is not readiang here.
        {
            bits_position++;
        }
        calculate_databit(bits_position);
        do
        {
            validation = 0;
            printf("Do you want to restart the program? (Y/N) ");
            scanf("%s", &input_rerun);
            switch(input_rerun)
            {
                case 'Y':
                    rerun = 0;
                    validation++;
                    break;
                case 'N':
                    rerun = 1;
                    validation++;
                    break;
                default:
                    printf("Please enter 'Y' or 'N'...\n\n");
                    break;
            }
        } while (validation ==0);
        } while(rerun != 1);      
}
int* assign_array(int bits_length, int change_bits, int assigned_data_stream)
{
    int counter = 0, bit_size = bits_length;
    int* new_data_stream = (int*) malloc(bits_length * sizeof(int));
    do
    {
        switch(input_datastream[bits_length])
        {
            case '1':
                new_data_stream[counter++] = (assigned_data_stream)? (counter == (change_bits))? 0: 1 : 1;
            break;
            case '0':
                new_data_stream[counter++] = (assigned_data_stream)? (counter == (change_bits))? 1: 0 : 0;
            break;      
        }
        bits_length--;
    } while(counter < bit_size);

    return new_data_stream;
}
int hamming(int* data_stream, int* data_stream_error, int bits_length)
{
    int sydrome_word = 0, c1, c2, c4, c8, c16, _c1, _c2, _c4, _c8, _c16;
    switch(bits_length)
    {
        case 8:
            c1 =  data_stream[0] ^ data_stream[1] ^ data_stream[3] ^ data_stream [4] ^ data_stream [6]; 
            c2 =  data_stream[0] ^ data_stream[2] ^ data_stream[3] ^ data_stream [5] ^ data_stream [6];
            c4 =  data_stream[1] ^ data_stream[2] ^ data_stream[3] ^ data_stream [7];
            c8 =  data_stream[4] ^ data_stream[5] ^ data_stream[6] ^ data_stream [7];

            _c1 =  data_stream_error[0] ^ data_stream_error[1] ^ data_stream_error[3] ^ data_stream_error [4] ^ data_stream_error [6]; 
            _c2 =  data_stream_error[0] ^ data_stream_error[2] ^ data_stream_error[3] ^ data_stream_error [5] ^ data_stream_error [6];
            _c4 =  data_stream_error[1] ^ data_stream_error[2] ^ data_stream_error[3] ^ data_stream_error [7];
            _c8 =  data_stream_error[4] ^ data_stream_error[5] ^ data_stream_error[6] ^ data_stream_error [7];
        break;
        case 16:
            c1 =  data_stream[0] ^ data_stream[1] ^ data_stream[3] ^ data_stream [4] ^ data_stream [6]  ^ data_stream[8] ^ data_stream[10] ^ data_stream[11] ^ data_stream[13] ^ data_stream[15]; 
            c2 =  data_stream[0] ^ data_stream[2] ^ data_stream[3] ^ data_stream [5] ^ data_stream [6] ^ data_stream[9] ^ data_stream[10] ^ data_stream[12] ^ data_stream[13];
            c4 =  data_stream[1] ^ data_stream[2] ^ data_stream[3] ^ data_stream [7] ^ data_stream[8] ^ data_stream[9] ^ data_stream[10] ^ data_stream[14] ^ data_stream[15];
            c8 =  data_stream[4] ^ data_stream[5] ^ data_stream[6] ^ data_stream [7] ^ data_stream[8] ^ data_stream[9] ^ data_stream[10];
            c16 = data_stream[11] ^ data_stream[12] ^ data_stream[13]  ^ data_stream[14] ^ data_stream[15];

            _c1 =  data_stream_error[0] ^ data_stream_error[1] ^ data_stream_error[3] ^ data_stream_error [4] ^ data_stream_error [6]  ^ data_stream_error[8] ^ data_stream_error[10] ^ data_stream_error[11] ^ data_stream_error[13] ^ data_stream_error[15]; 
            _c2 =  data_stream_error[0] ^ data_stream_error[2] ^ data_stream_error[3] ^ data_stream_error [5] ^ data_stream_error [6] ^ data_stream_error[9] ^ data_stream_error[10] ^ data_stream_error[12] ^ data_stream_error[13];
            _c4 =  data_stream_error[1] ^ data_stream_error[2] ^ data_stream_error[3] ^ data_stream_error [7] ^ data_stream_error[8] ^ data_stream_error[9] ^ data_stream_error[10] ^ data_stream_error[14] ^ data_stream_error[15];
            _c8 =  data_stream_error[4] ^ data_stream_error[5] ^ data_stream_error[6] ^ data_stream_error [7] ^ data_stream_error[8] ^ data_stream_error[9] ^ data_stream_error[10];
            _c16 = data_stream_error[11] ^ data_stream_error[12] ^ data_stream_error[13]  ^ data_stream_error[14] ^ data_stream_error[15];
        break;
    }

    printf("\nCheckbits for datastream : ");
    (bits_length == 8) ? printf("%d%d%d%d", c8,c4,c2,c1) : printf("%d%d%d%d%d",c16,c8,c4,c2,c1);
    
    printf("\nCheckbits for datastream with error: ");
    (bits_length == 8) ? printf("%d%d%d%d", _c8,_c4,_c2,_c1) : printf("%d%d%d%d%d",_c16,_c8,_c4,_c2,_c1);

    sydrome_word = (c1 ^ _c1) * pow(10,0) + (c2 ^ _c2)  * pow(10,1) + (c4 ^ _c4) * pow(10,2) + (c8 ^ _c8) * pow(10,3);
    if(bits_length == 16)
    {
        sydrome_word +=  (c16 ^ _c16) * pow(10,4);
    }

    printf("\nSydrome word :");
    (bits_length == 8) ? printf("%d%d%d%d", (c8 ^ _c8), (c4 ^ _c4), (c2 ^ _c2), (c1 ^ _c1)) : printf("%d%d%d%d%d", (c16 ^ _c16), (c8 ^ _c8), (c4 ^ _c4), (c2 ^ _c2), (c1 ^ _c1));
    
    return sydrome_word;
}
unsigned int get_bit_position(unsigned int bits_position) {
    switch(bits_position)
    {
        case 0:
        case 1:
        break;
        default:
          bits_position = (bits_position % 2) + 10 * get_bit_position(bits_position / 2);
          break;
    }
    return bits_position;
}
int calculate_databit(int bit_position)
{
    int c = 0, d = 0, counter = 1;
    for(int i = 0; i <= bit_position; i++)
    {
      if(pow(2,c) == counter)
      {
          c++;
         if (bit_position == counter)
         {
             printf("\n\nBit Error: %d\nCheckbits : C%d\n", bit_position, c);
         }
      }
      else
      {
          d++;
          if(bit_position == counter)
          {
              printf("\n\nBit Error: %d\nCheckbits : D%d\n", bit_position, d);
          }
        }
      counter++;
    }
}