#include "buffer.h"

// Creates a image buffer with default size (512 x 512 pixels)
Buffer::Buffer( void )
{
    // Allocate memory space for the image buffer
    buffer_data_.resize( h_resolution_, std::vector< glm::vec3 >( v_resolution_ ) );

    // Fills the image buffer with zeroes (black)
    for ( std::size_t y = 0; y < v_resolution_; y++ )
        for ( std::size_t x = 0; x < h_resolution_; x++ )
            buffer_data_[x][y] = glm::vec3{ 0.0f, 0.0f, 0.0f };
}

 // Creates a image buffer with a custom size (h_resolution x v_resolution pixels)
Buffer::Buffer( unsigned int h_resolution,
                unsigned int v_resolution ) :
        h_resolution_{ h_resolution },
        v_resolution_{ v_resolution }
{
    // Allocate memory space for the image buffer
    buffer_data_.resize( h_resolution_, std::vector< glm::vec3 >( v_resolution_ ) );

    // Fills the image buffer with zeroes (black)
    for ( std::size_t y = 0; y < v_resolution_; y++ )
        for ( std::size_t x = 0; x < h_resolution_; x++ )
            buffer_data_[x][y] = glm::vec3{ 0.0f, 0.0f, 0.0f };
}

Buffer::~Buffer( void )
{}

void Buffer::save( const std::string &filename ) const
{
    std::clog << "Buffer saving started... ";

    std::ofstream rendering_file;

    rendering_file.open( filename.c_str() );

    // Header of the PPM file. More on this filetype in:
    //     http://netpbm.sourceforge.net/doc/ppm.html
    rendering_file << "P3"
                   << std::endl
                   << h_resolution_
                   << " "
                   << v_resolution_
                   << std::endl
                   << 255
                   << std::endl;

    // Writes color data to the output PPM file
    for ( unsigned int y = 0; y < v_resolution_; y++)
    {
        for ( unsigned int x = 0; x < h_resolution_; x++ )
        {
            rendering_file << (int)(pow(clamp(buffer_data_[x][y][0]), 1.0f/2.2f)*255 + 0.5f) << " ";
            rendering_file << (int)(pow(clamp(buffer_data_[x][y][1]), 1.0f/2.2f)*255 + 0.5f) << " ";
            rendering_file << (int)(pow(clamp(buffer_data_[x][y][2]), 1.0f/2.2f)*255 + 0.5f) << " ";
        }
    }

    rendering_file.close();
    
    
    //Tranforming to png file
    Magick::Image img;
    
    try{
        img.read(filename);
    }catch(int error){
        std::cerr << "Cannot read file from path: " << filename << "." << std::endl
        << "Error: " << error << ". Terminating..." << std::endl;
        exit(1);
    }
    
    std::string str = filename;
    str[filename.size() - 2] = 'n';
    str[filename.size() - 1] = 'g';
    
    //Deleting original ppm file
    //unlink(filename.c_str());
    
    img.write(str);
    
    //Not proud of this unportable line of system call. Comment if it doesn't run, as it only opens the final file (optional)
    system((std::string("open " + str)).c_str());
    
    

    std::clog << "finished!\n";
}

