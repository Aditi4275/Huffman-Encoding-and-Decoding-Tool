# Huffman-Encoding-and-Decoding-Tool
This project implements a Huffman Encoding and Decoding Tool in C++ for efficient text compression and decompression. Huffman coding is a lossless data compression algorithm that assigns variable-length binary codes to characters based on their frequency in the input text, ensuring that the most frequently used characters have the shortest codes.

# Features:

Huffman Code Generation:
Calculates the frequency of characters in the input text.
Generates binary codes for each character based on a Huffman Tree.

Text Compression:
Converts the input text into a compressed binary string using the generated Huffman codes.
Saves the compressed data to a binary file.

Text Decompression:
Reconstructs the Huffman tree from the generated codes.
Decompresses the binary data back into the original text.

Save and Load Functionality:
Saves Huffman codes and compressed data to files.
Reads data back for decompression and validation.

# File Structure:
Input File:
A text file (input.txt) containing the original text to be compressed.

Compressed File:
A binary file (compressed.bin) storing the compressed representation of the input text.

Decompressed File:
A text file (decompressed.txt) containing the decompressed text, which should match the original input.

Huffman Codes File:
A file (huffman_codes.txt) containing the character-to-binary mappings used for compression.
