#include "serial_protocal.h"

#define PACKET_END 0xff
#define PACKET_START 0xff
#define PRINTF printf
//


void make_packet(char* data, char *send_buffer, int packet_id, int data_size, int* packet_size)
{
	unsigned int i = 0;
	char check_sum = 0;
	send_buffer[0] = 0xff;
	send_buffer[1] = packet_id;
	send_buffer[2] = (char)(data_size);
	for (i = 0; i < data_size; i++)
	{
		send_buffer[3 + i] = data[i];
		check_sum += (data[i] & 0x01);
	}
	send_buffer[3 + data_size + 0] = check_sum;
	send_buffer[3 + data_size + 1] = data_size;
	send_buffer[3 + data_size + 2] = packet_id;
	send_buffer[3 + data_size + 3] = 0xFF;
	*packet_size = data_size + 7;
}

//protocal form
//ff id size data_1 data_2 ... data_size checksum size id ff
//sample: ff 00 01 66 00 01 00 ff
int onRec(char c, char* rec_buffer, int* current_index, int *packet_id, int *_data_size, char* rec_packet)
{
	int data_size = 0;
	int check_sum = 0;
	int start_index  = 0 ;
	int i = 0;
	rec_buffer[*current_index] = c;
	if (*current_index >= 6 && (char)PACKET_END == c)
	{
		*packet_id = (char)rec_buffer[*current_index - 1];
		data_size = rec_buffer[*current_index - 2];
		start_index = *current_index - data_size - 3 - 3;
    PRINTF("e_id = %x\r\n", *packet_id);
    PRINTF("e_size = %x\r\n", data_size);
		//printf("id = %d\n", *packet_id);
    PRINTF("s_id = %x\r\n", rec_buffer[start_index + 1]);
    PRINTF("s_size = %x\r\n", rec_buffer[start_index + 2]);
    PRINTF("check_sum = %x\r\n", rec_buffer[start_index + 4 + data_size]);
		if (*current_index >= 6 - 1 + data_size)
		{
			//Length satisfied
			if (rec_buffer[start_index + 2] == data_size &&
				rec_buffer[start_index + 1] == *packet_id &&
				rec_buffer[start_index + 0] == (char)PACKET_START)
			{
				//protocol valid
				for (i = 0; i < data_size; i++)
				{
					rec_packet[i] = rec_buffer[start_index + 3 + i];
					check_sum += (rec_packet[i] & 0x01);
				}
				if (check_sum == rec_buffer[start_index + 3 + data_size])
				{
					*current_index = 0;
					*_data_size = data_size;
					/*printf("Get the message\r\n");
					for (i = 0; i < data_size; i++)
					cout << int(rec_packet[i]) << ",";
					cout << endl;*/
					return 1;
				}
			}
		}

	}
	*current_index = (*current_index + 1);
	return 0;
}
