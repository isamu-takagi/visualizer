#include "vizpointcloud.hpp"

const char* vshader_source =
R"(
    #version 300 es
    in mediump vec3 position;
    void main()
    {
        gl_PointSize = 5.0;
        gl_Position = vec4(position, 1);
    }
)";

const char* fshader_source =
R"(
    #version 300 es
    precision mediump float;
    uniform vec4 color;
    out vec4 my_FlagColor;
    void main()
    {
        my_FlagColor = color;
    }
)";

GLint VizPointCloud::program = -1;
GLint VizPointCloud::location_vertex = -1;
GLint VizPointCloud::location_color  = -1;

void VizPointCloud::init(QOpenGLFunctions *f)
{
    GLint status;
    GLint length;
    char message[1024];

    GLuint vshader = f->glCreateShader(GL_VERTEX_SHADER);
    f->glShaderSource(vshader, 1, &vshader_source, 0);
    f->glCompileShader(vshader);

    f->glGetShaderiv(vshader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
        f->glGetShaderiv(vshader, GL_INFO_LOG_LENGTH, &length);
        f->glGetShaderInfoLog(vshader, length, NULL, message);
        printf("vshader: %d %d %s\n", status, length, message);
    }

    GLuint fshader = f->glCreateShader(GL_FRAGMENT_SHADER);
    f->glShaderSource(fshader, 1, &fshader_source, 0);
    f->glCompileShader(fshader);

    f->glGetShaderiv(fshader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
        f->glGetShaderiv(fshader, GL_INFO_LOG_LENGTH, &length);
        f->glGetShaderInfoLog(fshader, length, NULL, message);
        printf("fshader: %d %d %s\n", status, length, message);
    }

    program = f->glCreateProgram();
    f->glAttachShader(program, vshader);
    f->glAttachShader(program, fshader);
    f->glLinkProgram(program);
    f->glDeleteShader(vshader);
    f->glDeleteShader(fshader);

    f->glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(status == GL_FALSE)
    {
        f->glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        f->glGetProgramInfoLog(program, length, NULL, message);
        printf("program: %d %d %s\n", status, length, message);
    }

    location_vertex = f->glGetAttribLocation(program, "position");
    location_color  = f->glGetUniformLocation(program, "color");

    printf("vshader: %d\n", vshader);
    printf("fshader: %d\n", fshader);
    printf("program: %d\n", program);
    printf("location_vertex: %d\n", location_vertex);
    printf("location_color : %d\n", location_color);
}

VizPointCloud::VizPointCloud(QOpenGLFunctions* f)
{
    f->glGenBuffers(1, &vbo);
}

void VizPointCloud::draw(QOpenGLFunctions* f)
{
    printf("Draw: location=%d size=%d\n", location_vertex, size);
    f->glUseProgram(program);
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo);
    f->glUniform4f(location_color, 1.0, 0.0, 0.0, 0.5);
    f->glEnableVertexAttribArray(location_vertex);
    f->glVertexAttribPointer(location_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    f->glDrawArrays(GL_POINTS, 0, size);
    f->glDisableVertexAttribArray(location_vertex);
}

void VizPointCloud::set_positions(QOpenGLFunctions* f, std::vector<GLfloat> positions)
{
    size = positions.size() / 3;
    f->glBindBuffer(GL_ARRAY_BUFFER, vbo);
    f->glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(GLfloat), positions.data(), GL_STATIC_DRAW);
}

