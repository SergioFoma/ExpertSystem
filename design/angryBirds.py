from PIL import Image
import os

size = 50
input_folder = "colorPicture/"
output_folder = "pictureAfterPython/"

''' get file names from cadrs '''
array_with_files_name = []
all_items = os.listdir( input_folder )
file_names = [ file_name  for file_name in all_items if os.path.isfile( os.path.join( input_folder, file_name ) ) ]
file_names.sort()

#print( file_names )

''' get black and white files in folder blackAndWhite '''
for fileName in file_names:
    with Image.open( input_folder + fileName ) as img:
        img_resized = img.resize( ( size, size ) )
        img_black_and_white = img_resized.convert( 'RGB' )
        img_black_and_white.save( output_folder + fileName )

new_all_items = os.listdir( output_folder )
output_file_names = [ ( output_folder + file_name ) for file_name in new_all_items if os.path.isfile( os.path.join( output_folder, file_name ) ) ]
output_file_names.sort( )

#print( output_file_names )

array_for_asm = []
for i in range( len( output_file_names ) ):
    img = Image.open( output_file_names[i] )
    matrix_with_color = [ [0] * size for x in range( size ) ]
    for x in range( size ):
        for  y in range( size ):
            pixel_color = img.getpixel( ( y, x ) )
            #print( pixel_color[0], pixel_color[1], pixel_color[ 2 ] )
            matrix_with_color[x][y] = pixel_color[0] * 256 ** 3 + pixel_color[1] * 256 ** 2 + pixel_color[0] * 256 + 32
    array_for_asm.append( matrix_with_color )

#for row in array_for_asm[29]:
#    print( row )
with open('fileForOutput.txt', 'w', encoding = 'utf-8' ) as asm_file:
    for matrix in array_for_asm:
        for x in range( size ):
            for y in range( size ):
                asm_file.write( str(matrix[x][y]) + ' ' )
            asm_file.write( "\n" )

print( (4278124064 // 256) % 256 )



