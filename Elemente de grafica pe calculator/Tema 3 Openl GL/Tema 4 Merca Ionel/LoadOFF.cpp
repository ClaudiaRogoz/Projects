#include "LoadOFF.h"
#include <iostream>

// GLUT variables 

static int GLUTwindow = 0;
static int GLUTwindow_height = 800;
static int GLUTwindow_width = 800;
static int GLUTmouse[2] = { 0, 0 };
static int GLUTbutton[3] = { 0, 0, 0 };
static int GLUTarrows[4] = { 0, 0, 0, 0 };
static int GLUTmodifiers = 0;



// Display variables

static int scaling = 0;
static int translating = 0;
static int rotating = 0;
static float scale = 1.0;
static float center[3] = { 0.0, 0.0, 0.0 };
static float rotation[3] = { 0.0, 0.0, 0.0 };
static float translation[3] = { 0.0, 0.0, -4.0 };

LoadOFF::LoadOFF(){
}


LoadOFF::LoadOFF(string file){
	LoadOFF::file = file;
	mesh = readoff();
}

Mesh* LoadOFF::readoff(){

	const char * filename = LoadOFF::file.c_str();
	int i;
	std::cout<<"FILENAME!!!!!!!!!!!!!!!!  "<<file<<endl;
	// Open file
	FILE *fp;
	if (!(fp = fopen(filename, "r"))) {
	  fprintf(stderr, "Unable to open file %s\n", filename);
	  return NULL;
	}

	// Allocate mesh structure
	Mesh *mesh = new Mesh();
	if (!mesh) {
	  fprintf(stderr, "Unable to allocate memory for file %s\n", filename);
	  fclose(fp);
	  return NULL;
	}

	// Read file
	int nverts = 0;
	int nfaces = 0;
	int nedges = 0;
	int line_count = 0;
	char buffer[1024];
	while (fgets(buffer, 1023, fp)) {
	  // Increment line counter
	  line_count++;

	  // Skip white space
	  char *bufferp = buffer;
	  while (isspace(*bufferp)) bufferp++;

	  // Skip blank lines and comments
	  if (*bufferp == '#') continue;
	  if (*bufferp == '\0') continue;

	  // Check section
	  if (nverts == 0) {
		// Read header 
		if (!strstr(bufferp, "OFF")) {
		  // Read mesh counts
		  if ((sscanf(bufferp, "%d%d%d", &nverts, &nfaces, &nedges) != 3) || (nverts == 0)) {
			fprintf(stderr, "Syntax error reading header on line %d in file %s\n", line_count, filename);
			fclose(fp);
			return NULL;
		  }

		  // Allocate memory for mesh
		  mesh->verts = new Vertex [nverts];
		  assert(mesh->verts);
		  mesh->faces = new Face [nfaces];
		  assert(mesh->faces);
		}
	  }
	  else if (mesh->nverts < nverts) {
		// Read vertex coordinates
		Vertex& vert = mesh->verts[mesh->nverts++];
		if (sscanf(bufferp, "%f%f%f", &(vert.x), &(vert.y), &(vert.z)) != 3) {
		  fprintf(stderr, "Syntax error with vertex coordinates on line %d in file %s\n", line_count, filename);
		  fclose(fp);
		  return NULL;
		}
	  }
	  else if (mesh->nfaces < nfaces) {
		// Get next face
		Face& face = mesh->faces[mesh->nfaces++];

		// Read number of vertices in face 
		bufferp = strtok(bufferp, " \t");
		if (bufferp) face.nverts = atoi(bufferp);
		else {
		  fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
		  fclose(fp);
		  return NULL;
		}

		// Allocate memory for face vertices
		face.verts = new Vertex *[face.nverts];
		assert(face.verts);

		// Read vertex indices for face
		for (i = 0; i < face.nverts; i++) {
		  bufferp = strtok(NULL, " \t");
		  if (bufferp) face.verts[i] = &(mesh->verts[atoi(bufferp)]);
		  else {
			fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
			fclose(fp);
			return NULL;
		  }
		}

		// Compute normal for face
		face.normal[0] = face.normal[1] = face.normal[2] = 0;
		Vertex *v1 = face.verts[face.nverts-1];
		for (i = 0; i < face.nverts; i++) {
		  Vertex *v2 = face.verts[i];
		  face.normal[0] += (v1->y - v2->y) * (v1->z + v2->z);
		  face.normal[1] += (v1->z - v2->z) * (v1->x + v2->x);
		  face.normal[2] += (v1->x - v2->x) * (v1->y + v2->y);
		  v1 = v2;
		}

		// Normalize normal for face
		float squared_normal_length = 0.0;
		squared_normal_length += face.normal[0]*face.normal[0];
		squared_normal_length += face.normal[1]*face.normal[1];
		squared_normal_length += face.normal[2]*face.normal[2];
		float normal_length = sqrt(squared_normal_length);
		if (normal_length > 1.0E-6) {
		  face.normal[0] /= normal_length;
		  face.normal[1] /= normal_length;
		  face.normal[2] /= normal_length;
		}
	  }
	  else {
		// Should never get here
		fprintf(stderr, "Found extra text starting at line %d in file %s\n", line_count, filename);
		break;
	  }
	}

	// Check whether read all faces
	if (nfaces != mesh->nfaces) {
	  fprintf(stderr, "Expected %d faces, but read only %d faces in file %s\n", nfaces, mesh->nfaces, filename);
	}

	// Close file
	fclose(fp);

	// Return mesh 
	return mesh;
}






LoadOFF::~LoadOFF(){

}


void LoadOFF::render(){

	// Set lights
	/*static GLfloat light0_position[] = { 3.0, 4.0, 5.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	static GLfloat light1_position[] = { -3.0, -2.0, -3.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);*/
	
  	// Set material
	static   GLfloat material_ambient1[] = { 0.14f, 0.46f, 0.3f, 1.0f };
	static   GLfloat material_diffuse1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse1);
	glMaterialfv(GL_FRONT,GL_SPECULAR,material_ambient1);

	// Draw faces
	for (int i = 0; i < mesh->nfaces; i++) {
	  Face& face = mesh->faces[i];
	  glBegin(GL_POLYGON);
	  glNormal3fv(face.normal);
	  for (int j = 0; j < face.nverts; j++) {
		Vertex *vert = face.verts[j];
		glVertex3f(vert->x, vert->y, vert->z);
	  }
	  glEnd();
	}

}

