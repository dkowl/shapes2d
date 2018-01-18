#pragma once
#include "List.h"
#include "ShapeWizard.h"
#include <memory>

namespace Shapes2D {

	template<typename TFloat>
	class ShapeStore {

		class ListNode;

		typedef List<ListNode> ShapeList;
		typedef std::shared_ptr<Shape<TFloat>> ShapePtr;

		ShapeList list;

	public:	

		void AddShape(ShapeType shapeType) {
			list.Add(ListNode(ShapePtr(ShapeWizard<TFloat>::CreateShape(shapeType)), shapeType));
		}

		void DeleteShape(const ListNode& shape) {
			list.Delete(shape);
		}

		void MoveShape(const ListNode &shape, Vector2<TFloat> v) {
			shape.shape->Move(v);
		}

		void ScaleShape(const ListNode &shape, TFloat x) {
			shape.shape->Scale(x);
		}

		void DisplayShapes() {
			for (auto&& node : list) {
				node.shape->Display();
			}
		}

		void DisplayShapes(ShapeType type) {
			for (auto&& node : list) {
				if(node.shapeType == type) node.shape->Display();
			}
		}

		ShapeList& GetShapeList() {
			return list;
		}

		void Save(std::ostream &os) {
			for (auto&& shape : list) {
				shape.Save(os);
				os << endl;
			}
		}

		void Load(std::istream &is) {
			int peekResult;
			while (true) {
				peekResult = (is >> std::ws).peek();
				if (peekResult == EOF) {
					is.ignore();
					is.clear();
					break;
				}
				ListNode listNode(is);
				list.Add(listNode);
			}
		}

	public:
		class ListNode {
		public:

			ShapePtr shape;
			ShapeType shapeType;
			int id;

			ListNode(std::istream &is) :
				id(GetNextId())
			{
				Load(is);
			}

			ListNode(ShapePtr shape, ShapeType shapeType) :
				id(GetNextId()),
				shape(shape),
				shapeType(shapeType)
			{
			}

			bool operator==(const ListNode &other) const {
				return id == other.id;
			}

			void Save(std::ostream &os) const {
				os << shapeType << " " << *shape;
			}

			void Load(std::istream &is) {
				int typeCode;
				is >> typeCode;
				shapeType = (ShapeType) typeCode;
				shape = ShapePtr(ShapeWizard<TFloat>::LoadShape(is, shapeType));
			}

		private:

			static int GetNextId() {
				static int id = -1;
				id++;
				return id;
			}
		};		
	};
}

