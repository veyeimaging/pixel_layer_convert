## Overview

This small tool converts the inconvenient raw data format on the Raspberry Pi and jetson platforms into a format that is easier for algorithms and display software to handle.
Note that not everyone needs this tool. It is basically just for the machine vision camera products produced by [www.veye.cc](http://www.veye.cc "www.veye.cc").

### Usage

#### make

```
git clone https://github.com/veyeimaging/pixel_layer_convert.git
make
```

#### usage

```
./pixel_layer_convert -I [input format] -i [inputfile] -o [outputfile]
```

The input and output formats are FourCC, which are listed below. The output format will automatically match the input format.
This tool does not require the width and height as parameters and will complete the conversion as much as possible.
The converted files can be easily opened using [vooya](https://www.offminor.de/ "vooya").
Note: The input format parameter is case-insensitive.

### input format

- Xavier

| Depth | Bit order (X is undefined) | FourCC |
| --- | --- | --- |
| 10 | 0 B9 B8 B7 B6 B5 B4 B3 B2 B1 B0 X X X X X | XY10 |
| 12 | 0 B11 B10 B9 B8 B7 B6 B5 B4 B3 B2 B1 B0 X X X | XY12 |

- TX2

| Depth | Bit order (X is undefined) | FourCC |
| --- | --- | --- |
| 10 | 0 0 B9 B8 B7 B6 B5 B4 B3 B2 B1 B0 X X X X | TY10 |
| 12 | 0 0 B11 B10 B9 B8 B7 B6 B5 B4 B3 B2 B1 B0 X X | TY12 |

- Raspberrypi mipi packed mode

<table>
<caption>12bit Y packed pixel layer(FourCC: Y12P)
</caption>
<tbody><tr>
<th colspan="8">Byte3
</th>
<th colspan="8">Byte2
</th>
<th colspan="8">Byte1
</th></tr>
<tr>
<td>bit7
</td>
<td>bit6
</td>
<td>bit5
</td>
<td>bit4
</td>
<td>bit3
</td>
<td>bit2
</td>
<td>bit1
</td>
<td>bit0
</td>
<td>bit7
</td>
<td>bit6
</td>
<td>bit5
</td>
<td>bit4
</td>
<td>bit3
</td>
<td>bit2
</td>
<td>bit1
</td>
<td>bit0
</td>
<td>bit7
</td>
<td>bit6
</td>
<td>bit5
</td>
<td>bit4
</td>
<td>bit3
</td>
<td>bit2
</td>
<td>bit1
</td>
<td>bit0
</td></tr>
<tr>
<td colspan="12">Pixel 2 data
</td>
<td colspan="12">Pixel 1 data
</td></tr></tbody></table>
<table>
<caption>10bit Y packed pixel layer(FourCC: Y10P)
</caption>
<tbody><tr>
<th colspan="8">Byte5
</th>
<th colspan="8">Byte4
</th>
<th colspan="8">Byte3
</th>
<th colspan="8">Byte2
</th>
<th colspan="8">Byte1
</th></tr>
<tr>
<td>bit7
</td>
<td>bit6
</td>
<td>bit5
</td>
<td>bit4
</td>
<td>bit3
</td>
<td>bit2
</td>
<td>bit1
</td>
<td>bit0
</td>
<td>bit7
</td>
<td>bit6
</td>
<td>bit5
</td>
<td>bit4
</td>
<td>bit3
</td>
<td>bit2
</td>
<td>bit1
</td>
<td>bit0
</td>
<td>bit7
</td>
<td>bit6
</td>
<td>bit5
</td>
<td>bit4
</td>
<td>bit3
</td>
<td>bit2
</td>
<td>bit1
</td>
<td>bit0
</td>
<td>bit7
</td>
<td>bit6
</td>
<td>bit5
</td>
<td>bit4
</td>
<td>bit3
</td>
<td>bit2
</td>
<td>bit1
</td>
<td>bit0
</td>
<td>bit7
</td>
<td>bit6
</td>
<td>bit5
</td>
<td>bit4
</td>
<td>bit3
</td>
<td>bit2
</td>
<td>bit1
</td>
<td>bit0
</td></tr>
<tr>
<td colspan="10">Pixel 4 data
</td>
<td colspan="10">Pixel 3 data
</td>
<td colspan="10">Pixel 2 data
</td>
<td colspan="10">Pixel 1 data
</td></tr></tbody></table>

### output format
The ouput unpacked format, i.e., using two bytes to store one pixel of data.
The valid data is filled in the lowest bit first, and the high bit that cannot be used is filled with 0.

| Depth | Bit order  | FourCC |
| --- | --- | --- |
| 10 | 0 0 0 0 0 0 B9 B8 B7 B6 B5 B4 B3 B2 B1 B0| 'Y10 ' |
| 12 | 0 0 0 0 B11 B10 B9 B8 B7 B6 B5 B4 B3 B2 B1 B0 | 'Y12 ' |
