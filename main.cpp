#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

#include "main.h"







int main(void)
{
	ofstream out_bin("points.bin", ios_base::binary);
	ofstream out_txt("points.txt");

	const size_t res = 100;
	const float grid_max = 1.5;
	const float grid_min = -grid_max;
	const unsigned short int max_iterations = 8;
	const float threshold = 4.0f;
	const float step_size = (grid_max - grid_min) / (res - 1);

	threeonion C;
	C.vertex_data[0] = 0.2f;
	C.vertex_data[1] = 0.5f;
	C.vertex_data[2] = 0.3f;

	threeonion Z;

	for (size_t i = 0; i < Z.vertex_length; i++)
		Z.vertex_data[i] = grid_min;

	size_t total_count = 0;
	size_t in_set = 0;

	for (size_t i0 = 0; i0 < res; i0++, Z.vertex_data[0] += step_size)
	{
		cout << i0 + 1 << " of " << res << endl;

		Z.vertex_data[1] = grid_min;

		for (size_t i1 = 0; i1 < res; i1++, Z.vertex_data[1] += step_size)
		{
			Z.vertex_data[2] = grid_min;

			for (size_t i2 = 0; i2 < res; i2++, Z.vertex_data[2] += step_size)
			{
				total_count++;

				float magnitude = iterate(Z, C, max_iterations, threshold);

				if (magnitude < threshold)
				{
					in_set++;

					out_bin.write(reinterpret_cast<const char*>(&Z.vertex_data[0]), sizeof(float));
					out_bin.write(reinterpret_cast<const char*>(&Z.vertex_data[1]), sizeof(float));
					out_bin.write(reinterpret_cast<const char*>(&Z.vertex_data[2]), sizeof(float));

					out_txt << Z.vertex_data[0] << " " << Z.vertex_data[1] << " " << Z.vertex_data[2] << endl;
				}
			}
		}
	}

	out_bin.close();
	out_txt.close();

	cout << in_set << " of " << total_count << endl;

	return 0;
}