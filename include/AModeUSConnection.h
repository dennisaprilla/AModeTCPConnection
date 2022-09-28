// basic libraries
#include <stdio.h>
#include <string>
#include <vector>
#include <stdint.h>

// this library if for managing file
#include <filesystem>
#include <fstream>
#include <iterator>
#include <boost/filesystem.hpp>

// these libraries is for windows connection
#include <winsock2.h>
#include <ws2tcpip.h>
// need to connect the lib that is needed by winsock 
#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

// Guillaume's libraries
// #include "Synch.h"
#include "getTime.h"

#include <opencv2/opencv.hpp>

#define DATA_RAW 0
#define DATA_DEPTH 1

#ifdef _WIN32
#define sleep Sleep
#else
#include <unistd.h>
#endif

/**
 * @brief AModeUSConnection used for handling the connection with A-mode Ultrasound Machine.
 */
class AModeUSConnection
{

private:
    // variables that stores the connection spec
    std::string ip_;
    std::string port_;
    SOCKET ConnectSocket_;

    // variables that stores amode spesifications
    int samples_, probes_, datalength_;
    int headersize_ = 4, indexsize_;

    // variable that controls the behavior of this class
    bool setrecord_ = false;
    bool usedataindex_ = false;
    bool firstpass_ = true;
    int datamode_ = DATA_RAW;
    std::string fullpath_;
    std::string recorddirectory_;

    // for logging data
    std::ofstream ofs_;

    // for testing
    int countdata_ = 0;
    std::stringstream filename_;

public:
    //constructors
    AModeUSConnection(std::string ip, std::string port, int mode);
    AModeUSConnection(std::string ip, std::string port, int samples, int probes);

    // to check whether the application is connected to the A-Mode Ultrasound Machine
    bool isConnected();
    // to determine we want to record the data or not, the default is false
    void setRecord(bool flag);
    // if the user wants to have index for every data received (maybe for debugging or something), the default is false
    void useDataIndex(bool flag);

    // to set where is the log file stored
    int setDirectory(std::string directory);
    int setDirectory(std::string directory, std::string filename);

    // for receiving data
    int receiveData();
    int receiveData(std::vector<uint16_t>* ultrasound_frd, char* receivebuffer, int receivebuffersize, int datasize, int headerindexsize);
    int receiveData(std::vector<double>* ultrasound_frd, char* receivebuffer, int receivebuffersize, int datasize, int headerindexsize);

    // for multithreading
    void operator()();

    bool userquit_ = false;                     //!< A flag which specified if the user wants to exit

protected:
    int connectTCP(SOCKET* ConnectSocket);

    /**
     * @brief If user pressed ESC, program halts and finished
    */
    bool checkKeyPressed()
    {
        return (GetKeyState(VK_ESCAPE) & 0x8000);
    }
};