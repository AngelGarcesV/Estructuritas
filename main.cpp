#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Graph.cpp"
#include "cmath"

using namespace std;



const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const sf::Color BACKGROUND_COLOR = sf::Color::Black;
const sf::Color VERTEX_COLOR = sf::Color::Green;
const sf::Color TEXT_COLOR = sf::Color::White;
const sf::Color EDGE_COLOR = sf::Color::Green;

class Information
{
public:
    vector<sf::VertexArray> aristas;
    vector<sf::CircleShape> vertices;
    Information(){
    }
    Information(vector<sf::VertexArray> aristas, vector<sf::CircleShape> vertices):aristas(aristas),vertices(vertices){};
};


void initializeGraph(Graph<string>& graph) {
    graph.addVertex("arroz");
    graph.addVertex("leche");
    graph.addVertex("pan");
    graph.addVertex("frijoles");
    graph.addVertex("azucar");
    graph.addVertex("aceite");
    graph.addVertex("sal");
    graph.addVertex("harina");

    graph.addEdge("arroz", "leche", 6);
    graph.addEdge("arroz", "pan", 2);
    graph.addEdge("leche", "pan", 12);
    graph.addEdge("frijoles", "azucar", 6);
    graph.addEdge("sal", "harina", 8);
    graph.addEdge("harina", "leche", 3);
    graph.addEdge("sal", "leche", 1);
    graph.addEdge("sal", "pan", 1);
    graph.addEdge("harina", "pan", 3);
    graph.addEdge("frijoles", "sal", 1);
    graph.addEdge("azucar", "sal", 5);
    graph.addEdge("arroz", "frijoles", 9);
    graph.addEdge("aceite", "sal", 7);
    graph.addEdge("aceite", "harina", 4);
    graph.addEdge("azucar", "harina", 3);
}

sf::Vector2f posicionVertice(int index,Graph<string>& graph){
    const float radius = 350;
    const float center_x = WINDOW_WIDTH / 2;
    const float center_y = (WINDOW_HEIGHT / 2) - 150;

    float angle = index * (2 * M_PI) / graph.vertexList.size();
    float x = center_x + radius * cos(angle);
    float y = center_y + radius * sin(angle);

    return sf::Vector2f(x, y);
}

sf::Vector2f posicionTexto(int index,Graph<string>& graph){

    sf::Vector2f vertexPosition = posicionVertice(index,graph);
    const float textOffsetX = 25;
    const float texoffsetY = 25;
    float x = vertexPosition.x + textOffsetX;
    float y = vertexPosition.y + texoffsetY;
    return sf::Vector2f(x, y);
}

sf::Vector2f posicionCentro(int index,Graph<string>& graph) {
    sf::Vector2f vertexPosition = posicionVertice(index,graph);
    const float radius = 30;
    float x = vertexPosition.x + radius;
    float y = vertexPosition.y + radius;
    return sf::Vector2f(x, y);
}

int getVertexIndex(Vertex<std::string>* vertex,Graph<string>& graph) {
    for (int i = 0; i < graph.vertexList.size(); i++) {
        if (graph.vertexList[i] == vertex)
            return i;
    }
    return -1;
}

sf::Vector2f getEdgeTextPosition(int fromIndex, int toIndex,Graph<string>& graph) {
    sf::Vector2f fromPosition = posicionVertice(fromIndex,graph);
    sf::Vector2f toPosition = posicionVertice(toIndex,graph);
    const float textOffsetX = 30;
    const float textOffsetY = -30;
    float x = (fromPosition.x + toPosition.x) / 2 + textOffsetX;
    float y = (fromPosition.y + toPosition.y) / 2 + textOffsetY;
    return sf::Vector2f(x, y);
}

vector<int> getPeso(Graph<string>& graph){
    vector<int> pesos;
    Vertex<string> *vertex;
    for (int i = 0; i < graph.vertexList.size(); i++) {
        vertex = graph.vertexList[i];
        for (Edge<string>* edge : vertex->connectedTo) {
            int weight = edge->weight;
            pesos.push_back(weight);
        }
    }

    return pesos;
}

bool pointPassesThroughLine(const sf::Vector2f& point, const sf::Vector2f& lineStart, const sf::Vector2f& lineEnd) {
    // Verificar si el punto está cerca de la línea dentro de una tolerancia
    const float tolerance = 5.f;

    float distanceToLine = std::abs((lineEnd.y - lineStart.y) * point.x - (lineEnd.x - lineStart.x) * point.y + lineEnd.x * lineStart.y - lineEnd.y * lineStart.x) / std::sqrt(std::pow(lineEnd.y - lineStart.y, 2) + std::pow(lineEnd.x - lineStart.x, 2));

    return distanceToLine < tolerance;
}

sf::Vector2f getCircleCenter(const sf::CircleShape& circle)
{
    sf::FloatRect bounds = circle.getGlobalBounds();
    sf::Vector2f center(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    return center;
}


bool isPointInsideCircle(const sf::Vector2f& point, const sf::Vector2f& circleCenter, float circleRadius)
{
    float distance = std::sqrt(std::pow(point.x - circleCenter.x, 2) + std::pow(point.y - circleCenter.y, 2));
    return (distance <= circleRadius);
}




Information drawGraph(Graph<string>& graph,sf::RenderWindow& window) {
    vector<sf::CircleShape> vertices;
    Information info;
    vector<sf::VertexArray> Aristas;
    sf::VertexArray lines(sf::Lines, 2);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "No se pudo cargar la fuente 'arial.ttf'" << std::endl;
        exit(0);
    }
    for (int i = 0; i < graph.vertexList.size(); i++) {
        Vertex<string>* vertex = graph.vertexList[i];
        sf::CircleShape circle(45);
        circle.setFillColor(VERTEX_COLOR);
        circle.setPosition(posicionVertice(i,graph));

        sf::Text text(vertex->data, font, 20);
        text.setFillColor(BACKGROUND_COLOR);
        text.setPosition(posicionTexto(i,graph));

        window.draw(circle);
        window.draw(text);
        vertices.push_back(circle);

        for (Edge<string>* edge : vertex->connectedTo) {
            Vertex<string>* toVertex = edge->to;
            int weight = edge->weight;


            lines[0].position = posicionCentro(i,graph);
            lines[1].position = posicionCentro(getVertexIndex(toVertex,graph),graph);
            lines[0].color = EDGE_COLOR;
            lines[1].color = EDGE_COLOR;

            window.draw(lines);
            Aristas.push_back(lines);

        }
    }
    info.aristas=Aristas;
    info.vertices=vertices;
    return info;
}

int main() {
    bool diferencia=false;
    vector<sf::CircleShape> vertices;
    Graph<std::string> graph;
    initializeGraph(graph);
    vector<sf::VertexArray> aristas;
    vector<int> pesos = getPeso(graph);
    bool showMessage = false;
    int peso=0;
    Information info;

    sf::Font font;
    font.loadFromFile("arial.ttf");


    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Grafo con SFML");
    sf::View view(sf::FloatRect(0, 0, 1920, 1080)); // Vista inicial de la ventana
    sf::RectangleShape rect(sf::Vector2f(1920, 2080));
    rect.setFillColor(sf::Color::Black);


    sf::RenderWindow menu(sf::VideoMode(600, 600), "SFML Rectangulos");

    // Crear los tres rectángulos
    sf::RectangleShape rectangle1(sf::Vector2f(250.f, 50.f));
    sf::Text text1("Crear Nodo)", font, 20);
    sf::RectangleShape rectangle2(sf::Vector2f(250.f, 50.f));
    sf::Text text2("Crear Arista", font, 20);
    sf::RectangleShape rectangle3(sf::Vector2f(250.f, 50.f));
    sf::Text text3("CERRAR PROGRAMA", font, 20);

    // Posicionamos los rectángulos
    rectangle1.setPosition(200.f, 175.f); // Puedes ajustar estas posiciones según tus necesidades
    text1.setFillColor(sf::Color::Black);
    text1.setPosition(220.f, 175.f);
    rectangle2.setPosition(200.f, 245.f); // El margen de 20 es agregado aquí
    text2.setPosition(220.f, 245.f);
    text2.setFillColor(sf::Color::Black);
    rectangle3.setPosition(200.f, 315.f); // El margen de 20 es agregado aquí
    text3.setPosition(220.f, 315.f);
    text3.setFillColor(sf::Color::Black);

    // Establecer colores para distinguir los rectángulos
    rectangle1.setFillColor(sf::Color::Red);
    rectangle2.setFillColor(sf::Color::Red);
    rectangle3.setFillColor(sf::Color::Red);
    menu.display();


    while (window.isOpen() && menu.isOpen()) {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                diferencia=false;
                // Obtenemos la posición del clic en la ventana
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition, view);

                for (int i = 0; i < vertices.size(); ++i) {
                    sf::CircleShape temp=vertices[i];
                    sf::Vector2f centro=getCircleCenter(temp);
                    if(isPointInsideCircle(sf::Vector2f(worldPos),centro,temp.getRadius())){
                        graph.deleteVertex(i);
                        diferencia=true;
                    }
                }
                if (diferencia==false){
                    for (int i = 0; i < aristas.size(); ++i) {
                        sf::VertexArray temp = aristas[i];
                        if (pointPassesThroughLine(sf::Vector2f(worldPos),temp[0].position, temp[1].position))
                        {

                            peso=pesos[i];
                            showMessage = true;
                        }
                    }
                }



            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                view.move(-10, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                view.move(10, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                view.move(0, -10);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                view.move(0, 10);
        }
        while (menu.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                menu.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(menu); // Posición del ratón en la ventana
                    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                    //boton 1 crear nodo
                    if (rectangle1.getGlobalBounds().contains(mousePosF)) { // Si el ratón está dentro del primer rectángulo

                        std::cout << "Crear Nodo" << std::endl;
                    }else if(rectangle2.getGlobalBounds().contains(mousePosF)){
                        cout<<"crear arista"<<endl;
                    }else if(rectangle3.getGlobalBounds().contains(mousePosF)){
                        cout<<"cerrar"<<endl;
                        window.close();
                        menu.close();
                    }
                }
            }
        }


        menu.clear(sf::Color::White);
        menu.draw(rectangle1);
        menu.draw(text1);
        menu.draw(rectangle2);
        menu.draw(text2);
        menu.draw(rectangle3);
        menu.draw(text3);
        menu.display();


        sf::Text message("Has tocado la linea con peso "+ to_string(peso), font, 24);
        message.setFillColor(sf::Color::White);
        message.setPosition(100, 100);

        window.clear(BACKGROUND_COLOR);
        window.setView(view);
        window.draw(rect);
        if (showMessage) {
            window.draw(message);
        }
        info=drawGraph(graph,window);
        aristas=info.aristas;
        vertices=info.vertices;
        window.display();}
    return 0;

    }




