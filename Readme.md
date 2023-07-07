### Build fdk-aac

###### Download of fdk-aac-2.0.1.tar.gz:
    https://sourceforge.net/projects/opencore-amr/files/fdk-aac/

###### uzip & configure:
    tar -zxvf fdk-aac-2.0.1.tar.gz
    # create build folder 
    mkdir build 
    cd build
    # check the path of the destination folder
    pwd 
    cd ..
    # for example mips architecture,
    ./configure --enable-static --host=mips-linux CC=rsdk-linux-gcc CXX=rsdk-linux-g++ --prefix=(your build fdk_aac path)
###### compile: 
    make -j8

###### install:
    make install

### Build library encapsulates PCM to AAC
###### copy resource: 
    cp -r (your build fdk_aac path)/lib/* ./libs/fdk-aac-mips-2.0.1/lib
    cp -r (your build fdk_aac path)/inclue/* ./libs/fdk-aac-mips-2.0.1/inclue
###### edit Makefile.sdk.conf : 
    ARCH_MIPS =1
    #OR
    # ARCH_ARM =1
###### Compile lib:
    make clean 
    make lib

### Example :

    unsigned int outputBuffer[4096] = {0};
	int outputSize = 0;

	if (aacEncInit(16000,16,1))
	{
	    printf("aac init fail \n");
	}

    while(1)
    {
        outputSize = aacEncode(buffer->vm_addr, buffer->bytesused, outputBuffer);
    }

	aacEncEnd();



