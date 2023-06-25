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
    graph.addVertex("P",'P');
    graph.addVertex("1B",'B');
    graph.addVertex("2B",'B');
    graph.addVertex("3B",'B');
    graph.addVertex("4B",'B');
    graph.addVertex("5B",'B');
    graph.addVertex("6B",'B');
    graph.addVertex("7B",'B');
    graph.addVertex("8B",'B');
    graph.addVertex("9B",'B');
    graph.addVertex("10B",'B');
    graph.addVertex("11B",'B');
    graph.addVertex("12B",'B');
    graph.addVertex("13B",'B');
    graph.addVertex("14B",'B');
    graph.addVertex("15B",'B');
    graph.addVertex("16B",'B');
    graph.addVertex("17B",'B');
    graph.addVertex("18B",'B');
    graph.addVertex("19B",'B');
    graph.addVertex("20B",'B');
    graph.addVertex("21B",'B');
    graph.addVertex("22B",'B');

    graph.addVertex("1",'A');
    graph.addVertex("2",'A');
    graph.addVertex("3",'A');
    graph.addVertex("4",'A');
    graph.addVertex("5",'A');
    graph.addVertex("6",'A');
    graph.addVertex("7",'A');
    graph.addVertex("8",'A');
    graph.addVertex("9",'A');
    graph.addVertex("10",'A');
    graph.addVertex("11",'A');
    graph.addVertex("12",'A');

    graph.addVertex("1",'C');
    graph.addVertex("2",'C');
    graph.addVertex("3",'C');

    graph.addEdge("1B", "22B", 6);
    graph.addEdge("22B", "1B", 2);

    graph.addEdge("1B", "4B", 12);
    graph.addEdge("4B", "1B", 6);

    graph.addEdge("1B", "5B", 8);
    graph.addEdge("5B", "1B", 3);

    graph.addEdge("1B", "7B", 1);
    graph.addEdge("7B", "1B", 1);

    graph.addEdge("1B", "8B", 3);
    graph.addEdge("8B", "1B", 1);

    graph.addEdge("1B", "9B", 5);
    graph.addEdge("9B", "1B", 9);

    graph.addEdge("1B", "6B", 7);
    graph.addEdge("6B", "1B", 4);

    graph.addEdge("1B", "14B", 7);
    graph.addEdge("14B", "1B", 4);

    graph.addEdge("1B", "2B", 7);
    graph.addEdge("2B", "1B", 4);

    graph.addEdge("1B", "16B", 7);
    graph.addEdge("16B", "1B", 4);

    graph.addEdge("9B", "10B", 7);
    graph.addEdge("10B", "9B", 4);

    graph.addEdge("11B", "9B", 7);
    graph.addEdge("9B", "11B", 4);

    graph.addEdge("11B", "13B", 7);
    graph.addEdge("13B", "11B", 4);

    graph.addEdge("11B", "12B", 7);
    graph.addEdge("12B", "11B", 4);

    graph.addEdge("2B", "3B", 7);
    graph.addEdge("3B", "2B", 4);

    graph.addEdge("14B", "15B", 7);
    graph.addEdge("15B", "14B", 4);

    graph.addEdge("16B", "17B", 7);
    graph.addEdge("17B", "16B", 4);

    graph.addEdge("17B", "18B", 7);
    graph.addEdge("18B", "17B", 4);

    graph.addEdge("17B", "19B", 7);
    graph.addEdge("19B", "17B", 4);

    graph.addEdge("16B", "20B", 7);
    graph.addEdge("20B", "16B", 4);

    graph.addEdge("16B", "21B", 7);
    graph.addEdge("21B", "16B", 4);
}

sf::Vector2f posicionVertice(int index,Graph<string>& graph){
    const float radius = 550;
    const float center_x = WINDOW_WIDTH / 2;
    const float center_y = (WINDOW_HEIGHT / 2) + 50;
    float x, y;


    if (graph.vertexList[index]->principal==true){
        x=center_x;
        y=center_y;
    }
    else{
        float angle = index * (2 * M_PI) / graph.vertexList.size();
        x = center_x + radius * cos(angle);
        y = center_y + radius * sin(angle);
    }



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
        font.loadFromFile("C:\\Users\\SSD Core i7 10GB\\CLionProjects\\untitled25\\arial.ttf");
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
    string input;
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
    if (!font.loadFromFile("arial.ttf")) {
        font.loadFromFile("C:\\Users\\SSD Core i7 10GB\\CLionProjects\\untitled25\\arial.ttf");
    }


    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Grafo con SFML");
    sf::View view(sf::FloatRect(0, 0, 1920, 1080)); // Vista inicial de la ventana
    sf::RectangleShape rect(sf::Vector2f(1920, 2080));
    rect.setFillColor(sf::Color::Black);
        while (window.isOpen()) {
            // Procesar eventos
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode < 128)
                    {
                        input += static_cast<char>(event.text.unicode);

                        if (event.text.unicode == '\r' || event.text.unicode == '\n')
                        {
                            std::cout << "Entrada del usuario: " << input << std::endl;
                            input.clear();
                        }
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition, view);

                    for (int i = 0; i < vertices.size(); ++i) {
                        sf::CircleShape temp=vertices[i];
                        sf::Vector2f centro=getCircleCenter(temp);
                        if(isPointInsideCircle(sf::Vector2f(worldPos),centro,temp.getRadius())){
                            if ((graph.vertexList[i]->sede=='A'&& graph.antonio== false)||(graph.vertexList[i]->sede=='B'&& graph.barcelona== false)||(graph.vertexList[i]->sede=='C'&& graph.boquemonte== false)){
                                graph.vertexList[i]->principal=true;
                            }
                        }
                    }
                }

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
            window.display();
            }




    return 0;
    }

