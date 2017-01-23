bitmap_data_visualization
=========================

Print Matrix on bit map file. 16 depth, 24 bit depth, 32 bit depth are all okay.

[How to use]
```c++
#include "bmp.h"
const int width = 600;
const int height = 500;
unsigned char bitmap[height][width];
for(int i=0; i<height; i++)
    for(int j=0; j<width; j++)
        bitmap[i][j]=(i*j)%256;
save_data_as_bitmap(bitmap, width, height, "data.jpg");
```
Note: this project has been used in other projects of mine:

computer graphics : ray trace app; ==> embedded for saving shots of 3D animation.

sophisticated system : civilization evolution simulation visualization.

deep learning : auto layout neuron network applied on MNIST/CIFAR-10/CIFAR-100/ST-10/SVHN image datasets.

